#pragma once

#include "ShaderImpl.h"

class ShaderLoader
{
public:
	static GLuint LoadShader(GLenum shaderType, std::string const& source, GLuint shaderId);
};
