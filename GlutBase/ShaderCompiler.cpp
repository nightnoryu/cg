#include "pch.h"
#include "ShaderCompiler.h"

void ShaderCompiler::Compile(GLuint shader)
{
	ShaderHandle handle(shader);
	handle.Compile();

	if (handle.GetParameter(GL_COMPILE_STATUS) != GL_TRUE)
	{
		std::stringstream message;
		message << "Shader " << shader << " compilation failed: " << handle.GetInfoLog();

		throw std::runtime_error(message.str());
	}
}
