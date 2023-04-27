#pragma once

#include "common_inc.h"

class ShaderBase
{
public:
	ShaderBase(ShaderBase const&) = delete;
	ShaderBase& operator=(ShaderBase const&) = delete;

	void SetSource(GLsizei count, GLchar const** strings, GLint const* lengths);

	void Compile();

protected:
	ShaderBase(GLuint shader = 0);

	~ShaderBase() = default;

private:
	GLuint m_shader;
};
