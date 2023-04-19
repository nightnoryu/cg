#include "Cuboid.h"

void Cuboid::Draw() const
{
	static float const vertices[8][3] = {
		{ -1, -1, -1 }, // 0
		{ +1, -1, -1 }, // 1
		{ +1, +1, -1 }, // 2
		{ -1, +1, -1 }, // 3
		{ -1, -1, +1 }, // 4
		{ +1, -1, +1 }, // 5
		{ +1, +1, +1 }, // 6
		{ -1, +1, +1 }, // 7
	};

	struct CubeFace
	{
		unsigned char vertex0;
		unsigned char vertex1;
		unsigned char vertex2;
		unsigned char vertex3;
		GLfloat tex0s, tex0t;
		GLfloat tex1s, tex1t;
		GLfloat tex2s, tex2t;
		GLfloat tex3s, tex3t;
	};

	static const CubeFace faces[] = {
		{ 4, 7, 3, 0, 0, 4, 0, 0, 4, 0, 4, 4 }, // грань x<0
		{ 5, 1, 2, 6, 4, 4, 0, 4, 0, 0, 4, 0 }, // грань x>0
		{ 4, 0, 1, 5, 0, 4, 0, 0, 4, 0, 4, 4 }, // грань y<0
		{ 7, 6, 2, 3, 0, 0, 4, 0, 4, 4, 0, 4 }, // грань y>0
		{ 0, 3, 2, 1, 0, 4, 0, 0, 4, 0, 4, 4 }, // грань z<0
		{ 4, 5, 6, 7, 0, 0, 4, 0, 4, 4, 0, 4 }, // грань z>0
	};
	static unsigned const faceCount = sizeof(faces) / sizeof(*faces);

	for (unsigned faceIndex = 0; faceIndex < faceCount; ++faceIndex)
	{
		CubeFace const& face = faces[faceIndex];

		m_texture.Bind();

		// Рисуем 4 вершины квадрата
		glBegin(GL_QUADS);
		{
			glTexCoord2f(face.tex0s, face.tex0t);
			glVertex3fv(vertices[face.vertex0]);

			glTexCoord2f(face.tex1s, face.tex1t);
			glVertex3fv(vertices[face.vertex1]);

			glTexCoord2f(face.tex2s, face.tex2t);
			glVertex3fv(vertices[face.vertex2]);

			glTexCoord2f(face.tex3s, face.tex3t);
			glVertex3fv(vertices[face.vertex3]);
		}
		glEnd();
	}
}

void Cuboid::SetStartingPoint(glm::vec3 point)
{
	m_startingPoint = point;
}

void Cuboid::SetDimensions(glm::vec3 dimensions)
{
	m_dimensions = dimensions;
}

void Cuboid::SetTexture(TextureHandle const& texture)
{
	m_texture = texture;
}
