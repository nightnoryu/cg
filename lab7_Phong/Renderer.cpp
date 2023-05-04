#include "Renderer.h"

using namespace boost::interprocess::ipcdetail;
using boost::mutex;

bool Renderer::IsRendering() const
{
	return atomic_read32(const_cast<boost::uint32_t volatile*>(&m_rendering)) != 0;
}
