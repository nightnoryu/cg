#include "ShapeDrawer.h"

void ShapeDrawer::DrawRectangle(float x, float y, float width, float height, glm::vec3 color)
{
	glColor3fv(glm::value_ptr(color));
	glRectf(x, y, x + width, y + height);
}

void ShapeDrawer::DrawFilledCircle(float cx, float cy, float radius, glm::vec3 color)
{
	glColor3fv(glm::value_ptr(color));

	auto const step = static_cast<float>(2 * std::numbers::pi / CIRCLE_POINTS);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy);
	for (float angle = 0; angle <= 2 * std::numbers::pi; angle += step)
	{
		float a = (fabsf(static_cast<float>(angle - 2 * std::numbers::pi)) < 1e-5) ? 0 : angle;
		float const dx = radius * cosf(a);
		float const dy = radius * sinf(a);
		glVertex2f(dx + cx, dy + cy);
	}
	glEnd();
}

void ShapeDrawer::DrawHollowCircle(float cx, float cy, float radius, glm::vec3 color)
{
	glColor3fv(glm::value_ptr(color));

	auto const step = static_cast<float>(2 * std::numbers::pi / CIRCLE_POINTS);

	glBegin(GL_LINE_LOOP);
	glVertex2f(cx, cy);
	for (float angle = 0; angle <= 2 * std::numbers::pi; angle += step)
	{
		float a = (fabsf(static_cast<float>(angle - 2 * std::numbers::pi)) < 1e-5) ? 0 : angle;
		float const dx = radius * cosf(a);
		float const dy = radius * sinf(a);
		glVertex2f(dx + cx, dy + cy);
	}
	glEnd();
}

void ShapeDrawer::DrawTriangle(glm::vec2 vertex1, glm::vec2 vertex2, glm::vec2 vertex3, glm::vec3 color)
{
	glColor3fv(glm::value_ptr(color));

	glBegin(GL_TRIANGLE_FAN);
	glVertex2fv(glm::value_ptr(vertex1));
	glVertex2fv(glm::value_ptr(vertex2));
	glVertex2fv(glm::value_ptr(vertex3));
	glEnd();
}
