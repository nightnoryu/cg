#include "Application.h"

Application app("Phong");

int main()
{
	glewInit();

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
