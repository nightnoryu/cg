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
	glClearColor(0.5, 0.5, 0.5, 1);
	glColor3f(1, 1, 1);

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

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2d(-0.8, -0.8);

		glTexCoord2f(4, 0);
		glVertex2d(0.8, -0.8);

		glTexCoord2f(4, 4);
		glVertex2d(0.8, 0.8);

		glTexCoord2f(0, 4);
		glVertex2d(-0.8, 0.8);
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
	glOrtho(-aspect, +aspect, -1, 1, 0, 10);
	glMatrixMode(GL_MODELVIEW);
}

void Application::InitShaders()
{
	ShaderLoader loader;
	Shader vertexShader = loader.LoadShader(GL_VERTEX_SHADER, "Shaders/checker.vsh");
	Shader fragmentShader = loader.LoadShader(GL_FRAGMENT_SHADER, "Shaders/checker.fsh");

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
