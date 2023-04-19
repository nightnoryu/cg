#pragma once

#include "TextureHandle.h"

class TextureLoader
{
public:
	TextureHandle LoadTexture(std::string const& filename, GLuint textureName = 0, GLuint level = 0) const;

	void SetMinFilter(GLenum filter);
	void SetMagFilter(GLenum filter);

	void SetWrapMode(GLenum wrapS, GLenum wrapT);

private:
	GLenum m_minFilter = GL_LINEAR;
	GLenum m_magFilter = GL_LINEAR;
	GLenum m_wrapS = GL_REPEAT;
	GLenum m_wrapT = GL_REPEAT;
};
