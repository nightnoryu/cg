#pragma once

#include <boost/thread.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>

class FrameBuffer
{
public:
	FrameBuffer(unsigned width, unsigned height);

	unsigned GetWidth() const;
	unsigned GetHeight() const;

	void Clear(boost::uint32_t color = 0);

	boost::uint32_t const* GetPixels(unsigned row = 0) const;
	boost::uint32_t* GetPixels(unsigned row = 0);

	boost::uint32_t GetPixel(unsigned x, unsigned y) const;
	void SetPixel(unsigned x, unsigned y, boost::uint32_t color);

private:
	std::vector<boost::uint32_t> m_pixels;
	unsigned m_width;
	unsigned m_height;
};
