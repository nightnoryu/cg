#include "Application.h"
#include "ProgramLinker.h"
#include "ShaderCompiler.h"
#include "ShaderLoader.h"

Application::Application(char const* title)
	: BaseApplication(title, 800, 600)
{
}

void Application::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);

	glLoadIdentity();
	gluLookAt(
		0, 0.7, 5,
		0, 0.7, 0,
		0, 1, 0);

	InitShaders();
}

void Application::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_program);

	glBegin(GL_LINE_STRIP);
	{
		for (double x = 0; x <= 2 * std::numbers::pi; x += std::numbers::pi / 1000)
		{
			glVertex2d(x, 0);
		}
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
	ShaderLoader loader;
	Shader vertexShader = loader.LoadShader(GL_VERTEX_SHADER, "Shaders/cannabola.vsh");
	Shader fragmentShader = loader.LoadShader(GL_FRAGMENT_SHADER, "Shaders/cannabola.fsh");

	ShaderCompiler compiler;
	compiler.Compile(vertexShader);
	compiler.Compile(fragmentShader);

	m_program.Create();
	m_program.AttachShader(vertexShader);
	m_program.AttachShader(fragmentShader);

	compiler.CheckStatus();

	ProgramLinker linker;
	linker.LinkProgram(m_program);

	linker.CheckStatus();
}
