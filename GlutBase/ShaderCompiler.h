#pragma once

#include "ShaderImpl.h"

class ShaderCompiler // TODO: strange architecture
{
public:
	ShaderCompiler() = default;

	void Compile(GLuint shader);
	void CheckStatus();

private:
	std::vector<GLuint> m_shaders;
};
