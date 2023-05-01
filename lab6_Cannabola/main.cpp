#include "Application.h"

Application app("Cannabola");

int main()
{
	glewInit();
	if (!GLEW_ARB_shader_objects)
	{
		return -1;
	}

	try
	{
		app.MainLoop();
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
