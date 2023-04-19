#pragma once

#include "common_inc.h"

class TextureHandle
{
public:
	TextureHandle() = default;
	TextureHandle(GLuint texture);

	void Delete() noexcept;
	void Bind() const;

	operator GLuint() const;

private:
	GLuint m_texture = 0;
};
