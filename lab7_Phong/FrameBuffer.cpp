#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned width, unsigned height)
	: m_pixels(width * height)
	, m_width(width)
	, m_height(height)
{
}

unsigned FrameBuffer::GetWidth() const
{
	return m_width;
}

unsigned FrameBuffer::GetHeight() const
{
	return m_height;
}

void FrameBuffer::Clear(boost::uint32_t color)
{
	std::fill(m_pixels.begin(), m_pixels.end(), color);
}

boost::uint32_t const* FrameBuffer::GetPixels(unsigned row) const
{
	return &m_pixels[row * m_width];
}

boost::uint32_t* FrameBuffer::GetPixels(unsigned row)
{
	return &m_pixels[row * m_width];
}

boost::uint32_t FrameBuffer::GetPixel(unsigned x, unsigned y) const
{
	return m_pixels[y * m_width + x];
}

void FrameBuffer::SetPixel(unsigned x, unsigned y, boost::uint32_t color)
{
	m_pixels[y * m_width + x] = color;
}
