#include "ShaderLoader.h"

GLuint ShaderLoader::LoadShader(GLenum shaderType, std::string const& source, GLuint shaderId)
{
	Shader shader(shaderId);
	if (!shader)
	{
		shader.Create(shaderType);
	}
	shader.SetSource(source.c_str());

	return shader.Detach();
}
