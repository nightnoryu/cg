#include "Window.h"
#include "ShaderLoader.h"
#include "ShaderCompiler.h"
#include "ProgramLinker.h"

namespace
{
constexpr double FIELD_OF_VIEW = 60 * std::numbers::pi / 180.0;

constexpr double Z_NEAR = 0.1;
constexpr double Z_FAR = 20;

constexpr double DISTANCE_TO_ORIGIN = 10;
} // namespace

Window::Window(int w, int h, char const* title)
	: BaseWindow(w, h, title)
{
}

void Window::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	auto const proj = glm::perspective(FIELD_OF_VIEW, aspect, Z_NEAR, Z_FAR);
	glLoadMatrixd(&proj[0][0]);
	glMatrixMode(GL_MODELVIEW);
}

void Window::OnRunStart()
{
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	InitShaders();
}

void Window::InitShaders()
{
	ShaderLoader loader;
	Shader vertexShader = loader.LoadShader(GL_VERTEX_SHADER, "Shaders/vertex.vsh");
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

void Window::Draw(int width, int height) const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupCameraMatrix();
}

void Window::SetupCameraMatrix() const
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 const cameraMatrix = glm::lookAt(
		glm::vec3{ 0.0, 0.0, DISTANCE_TO_ORIGIN },
		glm::vec3{ 0.0, 0.0, 0.0 },
		glm::vec3{ 0.0, 1.0, 0.0 });
	glLoadMatrixd(&cameraMatrix[0][0]);
}
