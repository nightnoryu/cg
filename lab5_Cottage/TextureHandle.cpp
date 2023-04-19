#include "TextureHandle.h"

TextureHandle::TextureHandle(GLuint texture)
	: m_texture(texture)
{
}

void TextureHandle::Delete() noexcept
{
	if (m_texture)
	{
		glDeleteTextures(1, &m_texture);
	}
}

TextureHandle::operator GLuint() const
{
	return m_texture;
}

void TextureHandle::BindTo(GLenum target) const
{
	if (m_texture)
	{
		glBindTexture(target, m_texture);
	}
}
