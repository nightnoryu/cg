#include "Window.h"
#include <numbers>

namespace
{
	constexpr double FIELD_OF_VIEW = 60 * std::numbers::pi / 180.0;

	constexpr double Z_NEAR = 0.1;
	constexpr double Z_FAR = 10;

	constexpr double VIEWPORT = 20;
} // namespace

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
}

void Window::Draw(int width, int height)
{
	SetupProjectionMatrix(width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	m_pin.Draw();
}

void Window::SetupProjectionMatrix(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	auto const aspectRatio = double(width) / double(height);
	auto viewWidth = VIEWPORT;
	auto viewHeight = viewWidth;
	if (aspectRatio > 1.0)
	{
		viewWidth = viewHeight * aspectRatio;
	}
	else
	{
		viewHeight = viewWidth / aspectRatio;
	}
	glOrtho(-viewWidth * 0.5, viewWidth * 0.5, -viewHeight * 0.5, viewHeight * 0.5, -1.0, 1.0);
}
