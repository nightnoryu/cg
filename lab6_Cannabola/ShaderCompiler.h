#pragma once

#include "ShaderImpl.h"

class ShaderCompiler
{
public:
	ShaderCompiler() = default;

	ShaderCompiler(ShaderCompiler const&) = delete;
	ShaderCompiler& operator=(ShaderCompiler const&) = delete;

	void Compile(GLuint shader);
	void CheckStatus();

private:
	std::vector<GLuint> m_shaders;
};
