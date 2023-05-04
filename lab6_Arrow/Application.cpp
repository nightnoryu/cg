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

	glBegin(GL_POINTS);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, 0.5);
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

	ShaderCompiler compiler;
	compiler.Compile(vertexShader);
	compiler.Compile(fragmentShader);
	compiler.Compile(geometryShader);

	m_program.Create();
	m_program.AttachShader(vertexShader);
	m_program.AttachShader(fragmentShader);
	m_program.AttachShader(geometryShader);

	compiler.CheckStatus();

	m_program.SetParameter(GL_GEOMETRY_INPUT_TYPE_ARB, GL_POINTS);
	m_program.SetParameter(GL_GEOMETRY_OUTPUT_TYPE_ARB, GL_TRIANGLE_STRIP);
	m_program.SetParameter(GL_GEOMETRY_VERTICES_OUT_EXT, 4);

	ProgramLinker linker;
	linker.LinkProgram(m_program);

	linker.CheckStatus();
}
