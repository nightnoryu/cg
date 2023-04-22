#include "Window.h"
#include "DirectLight.h"

namespace
{
constexpr double FIELD_OF_VIEW = 60 * std::numbers::pi / 180.0;

constexpr double Z_NEAR = 0.1;
constexpr double Z_FAR = 20;

glm::dmat4x4 Orthonormalize(glm::dmat4x4 const& m)
{
	auto const normalizedMatrix = glm::orthonormalize(glm::dmat3x3{ m });
	return {
		glm::dvec4{ normalizedMatrix[0], 0.0 },
		glm::dvec4{ normalizedMatrix[1], 0.0 },
		glm::dvec4{ normalizedMatrix[2], 0.0 },
		m[3]
	};
}
} // namespace

Window::Window(int w, int h, char const* title)
	: BaseWindow(w, h, title)
{
	m_textureLoader.SetMagFilter(GL_NEAREST);
	m_textureLoader.SetMinFilter(GL_NEAREST);
}

Window::~Window() noexcept
{
	m_groundTexture.Delete();

	m_wallTexture.Delete();
	m_windowTexture.Delete();
	m_doorTopTexture.Delete();
	m_doorBottomTexture.Delete();
}

void Window::OnMouseButton(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		m_leftButtonPressed = (action & GLFW_PRESS) != 0;
	}
}

void Window::OnMouseMove(double x, double y)
{
	const glm::dvec2 mousePos{ x, y };
	if (m_leftButtonPressed)
	{
		auto const windowSize = GetFramebufferSize();

		auto const mouseDelta = mousePos - m_mousePos;
		double const xAngle = mouseDelta.y * std::numbers::pi / windowSize.y;
		double const yAngle = mouseDelta.x * std::numbers::pi / windowSize.x;
		RotateCamera(xAngle, yAngle);
	}
	m_mousePos = mousePos;
}

void Window::RotateCamera(double xAngleRadians, double yAngleRadians)
{
	const glm::dvec3 xAxis{
		m_cameraMatrix[0][0], m_cameraMatrix[1][0], m_cameraMatrix[2][0]
	};
	const glm::dvec3 yAxis{
		m_cameraMatrix[0][1], m_cameraMatrix[1][1], m_cameraMatrix[2][1]
	};
	m_cameraMatrix = glm::rotate(m_cameraMatrix, xAngleRadians, xAxis);
	m_cameraMatrix = glm::rotate(m_cameraMatrix, yAngleRadians, yAxis);

	m_cameraMatrix = Orthonormalize(m_cameraMatrix);
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
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);

	glEnable(GL_TEXTURE_2D);

	/*DirectLight light{ { 0.0f, 0.0f, 1.0f } };
	light.Apply(GL_LIGHT0);*/

	m_groundTexture = m_textureLoader.LoadTexture("Assets/grass_block_top.png");
	m_environment.SetGroundTexture(m_groundTexture);

	m_wallTexture = m_textureLoader.LoadTexture("Assets/bricks.png");
	m_cottage.SetWallTexture(m_wallTexture);

	m_windowTexture = m_textureLoader.LoadTexture("Assets/glass.png");
	m_cottage.SetWindowTexture(m_windowTexture);

	m_doorTopTexture = m_textureLoader.LoadTexture("Assets/birch_door_top.png");
	m_doorBottomTexture = m_textureLoader.LoadTexture("Assets/birch_door_bottom.png");
	m_cottage.SetDoorTextures(m_doorTopTexture, m_doorBottomTexture);
}

void Window::Draw(int width, int height)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupCameraMatrix();

	m_environment.Draw();
	m_cottage.Draw();
}

void Window::SetupCameraMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&m_cameraMatrix[0][0]);
}
