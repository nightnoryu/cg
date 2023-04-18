#pragma once

#include "common_inc.h"

class Dodecahedron
{
public:
	Dodecahedron();
	void Draw() const;

	void SetSideColor(std::size_t side, glm::vec4 const& color);

private:
	static inline double RATIO = 2 / (1 + std::sqrt(5));

	static double inline const VERTICES[20][3] = {
		{ 1, 1, 1 },
		{ +1, +1, -1 },
		{ +1, -1, +1 },
		{ +1, -1, -1 },
		{ -1, +1, +1 },
		{ -1, +1, -1 },
		{ -1, -1, +1 },
		{ -1, -1, -1 },

		{ 0, +(1 - RATIO * RATIO), +(1 + RATIO) },
		{ 0, +(1 - RATIO * RATIO), -(1 + RATIO) },
		{ 0, -(1 - RATIO * RATIO), +(1 + RATIO) },
		{ 0, -(1 - RATIO * RATIO), -(1 + RATIO) },

		{ +(1 - RATIO * RATIO), +(1 + RATIO), 0 },
		{ +(1 - RATIO * RATIO), -(1 + RATIO), 0 },
		{ -(1 - RATIO * RATIO), +(1 + RATIO), 0 },
		{ -(1 - RATIO * RATIO), -(1 + RATIO), 0 },

		{ +(1 + RATIO), 0, +(1 - RATIO * RATIO) },
		{ +(1 + RATIO), 0, -(1 - RATIO * RATIO) },
		{ -(1 + RATIO), 0, +(1 - RATIO * RATIO) },
		{ -(1 + RATIO), 0, -(1 - RATIO * RATIO) }
	};

	static constexpr int FACES[12][5] = {
		{ 8, 10, 2, 16, 0 },
		{ 12, 14, 4, 8, 0 },
		{ 16, 17, 1, 12, 0 },
		{ 17, 3, 11, 9, 1 },
		{ 9, 5, 14, 12, 1 },
		{ 10, 6, 15, 13, 2 },
		{ 13, 3, 17, 16, 2 },
		{ 13, 15, 7, 11, 3 },
		{ 18, 6, 10, 8, 4 },
		{ 14, 5, 19, 18, 4 },
		{ 9, 11, 7, 19, 5 },
		{ 6, 18, 19, 7, 15 },
	};
	static std::size_t constexpr FACE_COUNT = sizeof(FACES) / sizeof(*FACES);

	void DrawOutline() const;
	void DrawFaces(GLenum cullFace) const;

	glm::vec4 m_sideColors[12];
	glm::vec4 m_specularColor = { 0, 0, 0, 1 };
	float m_shininess = 1;
};
