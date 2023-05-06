#pragma once

#include "FrameBuffer.h"

class Renderer
{
public:
	~Renderer();

	bool IsRendering() const;
	bool GetProgress(unsigned& renderedChunks, unsigned& totalChunks) const;

	bool Render(FrameBuffer& buffer);
	void Stop();

private:
	void RenderFrame(FrameBuffer& buffer);

	bool SetRendering(bool rendering);
	bool SetStopping(bool stopping);

	bool IsStopping() const;

	boost::uint32_t CalculatePixelColor(int x, int y, unsigned frameWidth, unsigned frameHeight) const;

	boost::thread m_thread;
	mutable boost::mutex m_mutex;
	volatile boost::uint32_t m_rendering = 0;
	volatile boost::uint32_t m_stopping = 0;
	volatile boost::uint32_t m_totalChunks = 0;
	volatile boost::uint32_t m_renderedChunks = 0;
};
