#include "pch.h"
#include "ShaderCompiler.h"

void ShaderCompiler::Compile(GLuint shader)
{
	ShaderHandle handle(shader);
	handle.Compile();
	m_shaders.push_back(shader);
}

void ShaderCompiler::CheckStatus()
{
	std::stringstream ss;
	bool hasErrors = false;

	for (auto&& shader : m_shaders)
	{
		ShaderHandle handle(shader);
		if (handle.GetParameter(GL_COMPILE_STATUS) != GL_TRUE)
		{
			hasErrors = true;
			ss << "Shader " << shader << " compilation failed: " << handle.GetInfoLog() << "\n";
		}
	}

	m_shaders.clear();

	if (hasErrors)
	{
		throw std::runtime_error(ss.str());
	}
}
