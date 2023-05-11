#include "Application.h"
#include "ShaderLoader.h"

Application::Application(char const* title)
	: BaseApplication(title, 800, 600)
{
}

void Application::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glClearColor(1, 1, 1, 1);

	glLoadIdentity();
	gluLookAt(
		0, 0, 3,
		0, 0, 0,
		0, 1, 0);

	InitShaders();
}

void Application::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_program);

	// TODO: угол не должен зависеть от ширины окна
	glBegin(GL_LINES);
	{
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);

		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);

		glVertex2f(0, 0.1f);
		glVertex2f(0, 0.5f);
	}
	glEnd();

	glUseProgram(0);
}

void Application::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	glOrtho(-aspect, +aspect, -1, 1, 1, 50);
	glMatrixMode(GL_MODELVIEW);
}

void Application::InitShaders()
{
	if (!GLEW_EXT_geometry_shader4)
	{
		throw std::runtime_error("geometry shaders are not supported");
	}

	ShaderLoader loader;
	Shader vertexShader = loader.LoadShader(GL_VERTEX_SHADER, "Shaders/arrow.vsh");
	Shader fragmentShader = loader.LoadShader(GL_FRAGMENT_SHADER, "Shaders/arrow.fsh");
	Shader geometryShader = loader.LoadShader(GL_GEOMETRY_SHADER, "Shaders/arrow.gsh");

	vertexShader.Compile();
	fragmentShader.Compile();
	geometryShader.Compile();

	m_program.Create();
	m_program.AttachShader(vertexShader);
	m_program.AttachShader(fragmentShader);
	m_program.AttachShader(geometryShader);

	m_program.SetParameter(GL_GEOMETRY_INPUT_TYPE_ARB, GL_LINES);
	m_program.SetParameter(GL_GEOMETRY_OUTPUT_TYPE_ARB, GL_LINE_STRIP);
	m_program.SetParameter(GL_GEOMETRY_VERTICES_OUT_EXT, 5);

	m_program.Link();
}
