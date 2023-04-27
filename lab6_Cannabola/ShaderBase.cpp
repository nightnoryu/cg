#include "ShaderBase.h"

void ShaderBase::SetSource(GLsizei count, GLchar const** strings, GLint const* lengths)
{
	if (m_shader != 0)
	{
		glShaderSource(m_shader, count, strings, lengths);
	}
}

void ShaderBase::Compile()
{
	if (m_shader != 0)
	{
		glCompileShader(m_shader);
	}
}

ShaderBase::ShaderBase(GLuint shader)
	: m_shader(shader)
{
}
