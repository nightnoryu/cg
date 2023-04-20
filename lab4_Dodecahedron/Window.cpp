#include "Window.h"
#include "DirectLight.h"

namespace
{
// ���� ������ �� ���������
constexpr double FIELD_OF_VIEW = 60 * std::numbers::pi / 180.0;
// ������ ������� ����
constexpr double CUBE_SIZE = 1;

constexpr double Z_NEAR = 0.1;
constexpr double Z_FAR = 10;

// ������������� ������� 4*4 (��� ������ ���� �������� �������)
glm::dmat4x4 Orthonormalize(glm::dmat4x4 const& m)
{
	// ��������� ���������� 3*3 �� ������� m � ������������� �
	auto const normalizedMatrix = glm::orthonormalize(glm::dmat3x3{ m });
	// �������� 3 ������� �������� �������
	return {
		glm::dvec4{ normalizedMatrix[0], 0.0 },
		glm::dvec4{ normalizedMatrix[1], 0.0 },
		glm::dvec4{ normalizedMatrix[2], 0.0 },
		m[3]
	};
}

glm::vec4 ColorToVector(int color, float alpha)
{
	auto const red = static_cast<float>((color >> 16) & 0xff) / 255.0f;
	auto const green = static_cast<float>((color >> 8) & 0xff) / 255.0f;
	auto const blue = static_cast<float>(color & 0xff) / 255.0f;

	return { red, green, blue, alpha };
}
} // namespace

Window::Window(int w, int h, char const* title)
	: BaseWindow(w, h, title)
{
	m_dodecahedron.SetSideColor(0, ColorToVector(0x8250c4, SHAPE_ALPHA));
	m_dodecahedron.SetSideColor(1, ColorToVector(0x5ec8c8, SHAPE_ALPHA));
	m_dodecahedron.SetSideColor(2, ColorToVector(0xff977e, SHAPE_ALPHA));
	m_dodecahedron.SetSideColor(3, ColorToVector(0x5b2071, SHAPE_ALPHA));
	m_dodecahedron.SetSideColor(4, ColorToVector(0x95dabb, SHAPE_ALPHA));
	m_dodecahedron.SetSideColor(5, ColorToVector(0x33ae81, SHAPE_ALPHA));
	m_dodecahedron.SetSideColor(6, ColorToVector(0xd83b01, SHAPE_ALPHA));
	m_dodecahedron.SetSideColor(7, ColorToVector(0xffd86c, SHAPE_ALPHA));
	m_dodecahedron.SetSideColor(8, ColorToVector(0xccaa14, SHAPE_ALPHA));
	m_dodecahedron.SetSideColor(9, ColorToVector(0x004753, SHAPE_ALPHA));
	m_dodecahedron.SetSideColor(10, ColorToVector(0xc83d95, SHAPE_ALPHA));
	m_dodecahedron.SetSideColor(11, ColorToVector(0x499195, SHAPE_ALPHA));
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

// ������� ������ ������ ������ ���������
void Window::RotateCamera(double xAngleRadians, double yAngleRadians)
{
	// ��������� �� 1 � 2 ������ ������� ������ ����������� ���� ��������,
	// ����������� � ��������� ����� X � Y.
	// ������ ������, ��� ����� ���� ��������� ������� �� �������� ������� ������, �� ��� ���
	// ������� ������ �����������������, ���������� ��������������� � ���������� 3*3
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

	// ��������� ����������� ������ ���������� ������� ����
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	auto const proj = glm::perspective(FIELD_OF_VIEW, aspect, Z_NEAR, Z_FAR);
	glLoadMatrixd(&proj[0][0]);
	glMatrixMode(GL_MODELVIEW);
}

void Window::OnRunStart()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// �������� ����� ���������� ������
	glEnable(GL_CULL_FACE);
	// ��������������� ����� ��������� ������� ������
	glCullFace(GL_BACK);
	// ������� ��������� ��������� �������, ���� ��� �� ���������
	// ����� ������ �������������� ������ ������� �������
	glFrontFace(GL_CCW);

	// �������� ���� ������� ��� �������� ��������� ����� � ������������
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ����������� �� �������� ����� (��������� � �������� �����������)
	DirectLight light{ { 0.0f, 0.0f, 5.0f } };
	light.Apply(GL_LIGHT0);
}

void Window::Draw(int width, int height)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupCameraMatrix();

	m_dodecahedron.DrawSolidParts();

	glDepthMask(GL_FALSE);
	m_dodecahedron.DrawTransparentParts();
	glDepthMask(GL_TRUE);
}

void Window::SetupCameraMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&m_cameraMatrix[0][0]);
}
