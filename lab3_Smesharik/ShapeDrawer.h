#pragma once

#include "common_inc.h"

class ShapeDrawer
{
public:
	static void DrawRectangle(float x, float y, float width, float height, glm::vec3 color);

	static void DrawFilledCircle(float cx, float cy, float radius, glm::vec3 color);

	static void DrawHollowCircle(float cx, float cy, float radius, glm::vec3 color);

	static void DrawTriangle(glm::vec2 vertex1, glm::vec2 vertex2, glm::vec2 vertex3, glm::vec3 color);

private:
	static constexpr int CIRCLE_POINTS = 360;
};
