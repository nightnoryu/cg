#include "Application.h"

Application app("test");

int main()
{
	glewInit();
	if (!GLEW_ARB_shader_objects)
	{
		return -1;
	}

	app.MainLoop();
	return 0;
}
