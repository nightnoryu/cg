#include "GLFWInitializer.h"
#include "Window.h"

int main()
{
	try
	{
		GLFWInitializer initGLFW;
		Window window{ 800, 600, "Cannabola" };
		window.Run();
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
