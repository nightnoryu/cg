#include "Application.h"

Application::Application(char const* title)
	: BaseApplication(title)
{
}

void Application::OnInit()
{
	glClearColor(1, 1, 1, 1);
}

void Application::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0, 0, 1);
	FillEllipse(150, 120, 100, 90);
}

void Application::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void Application::FillEllipse(float x, float y, float rx, float ry, std::size_t points)
{

	float const step = 2 * std::numbers::pi / points;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x, y);
	for (float angle = 0; angle <= 2 * std::numbers::pi; angle += step)
	{
		float a = (fabsf(angle - 2 * std::numbers::pi) < 1e-5) ? 0 : angle;
		float const dx = rx * cosf(a);
		float const dy = ry * sinf(a);
		glVertex2f(dx + x, dy + y);
	}
	glEnd();
}
