#include "GLFWInitializer.h"
#include "Window.h"

int main()
{
	GLFWInitializer initGLFW;
	Window window(800, 600, "3D Dodecahedron");
	window.Run();
}