#include "GLFWInitializer.h"

GLFWInitializer::GLFWInitializer()
{
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}

	glewInit();
	/*if (!GLEW_ARB_shader_objects)
	{
		throw std::runtime_error("Shaders are not supported");
	}*/
}

GLFWInitializer::~GLFWInitializer()
{
	glfwTerminate();
}
