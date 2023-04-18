#include "Window.h"
#include "DirectLight.h"

namespace
{
// Угол обзора по вертикали
constexpr double FIELD_OF_VIEW = 60 * std::numbers::pi / 180.0;
// Размер стороны куба
constexpr double CUBE_SIZE = 1;

constexpr double Z_NEAR = 0.1;
constexpr double Z_FAR = 10;

// Ортонормируем матрицу 4*4 (это должна быть аффинная матрица)
glm::dmat4x4 Orthonormalize(glm::dmat4x4 const& m)
{
	// Извлекаем подматрицу 3*3 из матрицы m и ортонормируем её
	auto const normalizedMatrix = glm::orthonormalize(glm::dmat3x3{ m });
	// Заменяем 3 столбца исходной матрицы
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

GLuint LoadTexture(std::string const& filename)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, STBI_rgb);

	if (!data)
	{
		throw std::runtime_error("failed to load texture");
	}

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	return texture;
}
} // namespace

Window::Window(int w, int h, char const* title)
	: BaseWindow(w, h, title)
{
}

Window::~Window() noexcept
{
	if (m_texture)
	{
		glDeleteTextures(1, &m_texture);
	}
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

// Вращаем камеру вокруг начала координат
void Window::RotateCamera(double xAngleRadians, double yAngleRadians)
{
	// Извлекаем из 1 и 2 строки матрицы камеры направления осей вращения,
	// совпадающих с экранными осями X и Y.
	// Строго говоря, для этого надо извлекать столбцы их обратной матрицы камеры, но так как
	// матрица камеры ортонормированная, достаточно транспонировать её подматрицу 3*3
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

	// Вычисляем соотношение сторон клиентской области окна
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

	// Включаем режим отбраковки граней
	glEnable(GL_CULL_FACE);
	// Отбраковываться будут нелицевые стороны граней
	glCullFace(GL_BACK);
	// Сторона примитива считается лицевой, если при ее рисовании
	// обход верших осуществляется против часовой стрелки
	glFrontFace(GL_CCW);

	// Включаем тест глубины для удаления невидимых линий и поверхностей
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);

	// Направление на источник света (совпадает с позицией наблюдателя)
	/*DirectLight light{ { 0.0f, 0.0f, 1.0f } };
	light.SetDiffuseColor({ 0.5f, 0.5f, 0.5f, 1.0f });
	light.SetAmbientColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	light.SetSpecularColor({ 0.3f, 0.3f, 0.3f, 1.0f });
	light.Apply(GL_LIGHT0);*/

	m_texture = LoadTexture("Assets/bricks.png");
}

void Window::Draw(int width, int height)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupCameraMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glBegin(GL_QUADS);
	{
		glNormal3f(0, 0, 1);

		// верхний левый угол
		glTexCoord2f(0, 0);
		glVertex3f(-1, 1, 0);

		// нижний левый угол
		glTexCoord2f(0, 1);
		glVertex3f(-1, -1, 0);

		// нижний правый угол
		glTexCoord2f(1, 1);
		glVertex3f(1, -1, 0);

		// верхний правый угол
		glTexCoord2f(1, 0);
		glVertex3f(1, 1, 0);
	}
	glEnd();
}

void Window::SetupCameraMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&m_cameraMatrix[0][0]);
}
