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
		std::numbers::pi, 0, 8,
		std::numbers::pi, 0, 0,
		0, 1, 0);

	InitShaders();
}

void Application::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0, 1, 0);
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
	glOrtho(-aspect, +aspect, -1, 1, 0, 60);
	glMatrixMode(GL_MODELVIEW);
}

void Application::InitShaders()
{
	ShaderLoader loader;
	Shader vertexShader = loader.LoadShader(GL_VERTEX_SHADER, "Shaders/cannabola.vsh");

	ShaderCompiler compiler;
	compiler.Compile(vertexShader);

	m_program.Create();
	m_program.AttachShader(vertexShader);

	compiler.CheckStatus();

	ProgramLinker linker;
	linker.LinkProgram(m_program);

	linker.CheckStatus();
}
