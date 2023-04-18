#include "Dodecahedron.h"

Dodecahedron::Dodecahedron()
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	for (std::size_t i = 0; i < 12; ++i)
	{
		SetSideColor(i, defaultColor);
	}
}

void Dodecahedron::Draw() const
{
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specularColor));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);

	DrawOutline();
	DrawFaces(GL_FRONT);
	DrawFaces(GL_BACK);

	glFlush();
}

void Dodecahedron::SetSideColor(std::size_t side, glm::vec4 const& color)
{
	m_sideColors[side] = color;
}

void Dodecahedron::DrawOutline() const
{
	for (auto facePoints : FACES)
	{
		glColor4f(0, 0, 0, 1);
		glBegin(GL_LINE_STRIP);
		for (std::size_t i = 0; i < 5; ++i)
		{
			glVertex3dv(VERTICES[facePoints[i]]);
		}
		glEnd();
	}
}

void Dodecahedron::DrawFaces(GLenum cullFace) const
{
	glCullFace(cullFace);
	for (std::size_t face = 0; face < FACE_COUNT; ++face)
	{
		auto const facePoints = FACES[face];

		auto const p0 = glm::make_vec3(VERTICES[facePoints[0]]);
		auto const p1 = glm::make_vec3(VERTICES[facePoints[1]]);
		auto const p2 = glm::make_vec3(VERTICES[facePoints[2]]);
		auto const p3 = glm::make_vec3(VERTICES[facePoints[3]]);

		auto const v01 = p1 - p0;
		auto const v02 = p2 - p0;
		auto const normal = glm::normalize(glm::cross(v01, v02));

		glNormal3dv(glm::value_ptr(normal));

		glColor4fv(glm::value_ptr(m_sideColors[face]));
		glBegin(GL_TRIANGLE_FAN);
		for (std::size_t i = 0; i < 5; ++i)
		{
			glVertex3dv(VERTICES[facePoints[i]]);
		}
		glEnd();
	}
}
