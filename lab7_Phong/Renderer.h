#pragma once

#include "FrameBuffer.h"

class Renderer
{
public:
	bool IsRendering() const;
	bool GetProcess(unsigned& renderedChunks, unsigned& totalChunks) const;

	bool Render(FrameBuffer& buffer);
	void Stop();

private:
	void RenderFrame(FrameBuffer& buffer);

	bool SetRendering(bool rendering);
	bool SetStopping(bool stopping);

	boost::uint32_t CalculatePixelColor(int x, int y, unsigned frameWidth, unsigned frameHeight) const;

	boost::thread m_thread;
	mutable boost::mutex m_mutex;
	volatile boost::uint32_t m_rendering;
	volatile boost::uint32_t m_stopping;
	volatile boost::uint32_t m_totalChunks;
	volatile boost::uint32_t m_renderedChunks;
};
