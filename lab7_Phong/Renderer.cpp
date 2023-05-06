#include "Renderer.h"

using namespace boost::interprocess::ipcdetail;
using boost::mutex;

Renderer::~Renderer()
{
	Stop();
}

bool Renderer::IsRendering() const
{
	return atomic_read32(const_cast<boost::uint32_t volatile*>(&m_rendering)) != 0;
}

bool Renderer::GetProgress(unsigned& renderedChunks, unsigned& totalChunks) const
{
	mutex::scoped_lock lock(m_mutex);

	renderedChunks = atomic_read32(const_cast<boost::uint32_t volatile*>(&m_renderedChunks));
	totalChunks = atomic_read32(const_cast<boost::uint32_t volatile*>(&m_totalChunks));

	return totalChunks > 0 && renderedChunks == totalChunks;
}

bool Renderer::Render(FrameBuffer& buffer)
{
	if (!SetRendering(true))
	{
		return false;
	}

	mutex::scoped_lock lock(m_mutex);

	buffer.Clear();

	atomic_write32(&m_totalChunks, 0);
	atomic_write32(&m_renderedChunks, 0);

	if (SetStopping(false))
	{
		SetRendering(false);
		return false;
	}

	m_thread = boost::thread(&Renderer::RenderFrame, this, boost::ref(buffer));

	return true;
}

void Renderer::Stop()
{
	if (IsRendering())
	{
		SetStopping(true);
		m_thread.join();
		SetStopping(false);
	}
}

void Renderer::RenderFrame(FrameBuffer& buffer)
{
	int const width = buffer.GetWidth();
	int const height = buffer.GetHeight();

	atomic_write32(&m_totalChunks, height);

#ifdef _OPENMP
#pragma omp parallel for schedule(dynamic)
#endif

	for (int y = 0; y < height; ++y)
	{
		boost::uint32_t* rowPixels = buffer.GetPixels(y);

		if (!IsStopping())
		{
			for (int x = 0; x < width; ++x)
			{
				rowPixels[x] = CalculatePixelColor(x, y, width, height);
			}

			atomic_inc32(&m_renderedChunks);
		}
	}

	SetStopping(false);
	SetRendering(false);
}

bool Renderer::SetRendering(bool rendering)
{
	bool wasRendering = atomic_cas32(&m_rendering, rendering, !rendering) != 0;
	return wasRendering != rendering;
}

bool Renderer::SetStopping(bool stopping)
{
	bool wasStopping = atomic_cas32(&m_stopping, stopping, !stopping) != 0;
	return wasStopping != stopping;
}

bool Renderer::IsStopping() const
{
	return atomic_read32(const_cast<boost::uint32_t volatile*>(&m_stopping)) != 0;
}

boost::uint32_t Renderer::CalculatePixelColor(int x, int y, unsigned frameWidth, unsigned frameHeight) const
{
	double x0 = 2.0 * x / frameWidth - 1.5;
	double y0 = 2.0 * y / frameHeight - 1.0;

	double rho = sqrt((x0 - 0.25) * (x0 - 0.25) + y0 * y0);
	double theta = atan2(y0, x0 - 0.25);
	double rhoC = 0.5 - 0.5 * cos(theta);
	if (rho <= rhoC)
	{
		return 0x000000;
	}

	double re = 0, im = 0;

	int iterCount = 10000;
	while ((iterCount > 0) && (re * re + im * im < 1e18))
	{
		double re1 = re * re - im * im + x0;
		im = 2 * re * im + y0;
		re = re1;
		--iterCount;
	}

	boost::uint8_t r = static_cast<boost::uint8_t>((iterCount / 3) & 0xff);
	boost::uint8_t g = static_cast<boost::uint8_t>(iterCount & 0xff);
	boost::uint8_t b = static_cast<boost::uint8_t>((iterCount / 2) & 0xff);
	boost::uint8_t a = 0xff;
	return (a << 24) | (r << 16) | (g << 8) | b;
}
