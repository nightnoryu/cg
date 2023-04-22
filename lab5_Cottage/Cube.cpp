#include "Cube.h"

Cube::Cube(glm::vec3 position, float size)
	: m_position(position)
	, m_size(size)
{
	for (std::size_t i = 0; i < 8; ++i)
	{
		for (std::size_t j = 0; j < 3; ++j)
	{
			m_vertices[i][j] = (BASE_VERTICES[i][j] + 1) * m_size * 0.5f + m_position[j];
		}
	}
}

void Cube::Draw() const
{
	for (unsigned faceIndex = 0; faceIndex < FACE_COUNT; ++faceIndex)
	{
		CubeFace const& face = FACES[faceIndex];

		m_texture.Bind();

		glBegin(GL_QUADS);
		{
			glTexCoord2f(face.tex0s, face.tex0t);
			glVertex3fv(m_vertices[face.vertex0].data());

			glTexCoord2f(face.tex1s, face.tex1t);
			glVertex3fv(m_vertices[face.vertex1].data());

			glTexCoord2f(face.tex2s, face.tex2t);
			glVertex3fv(m_vertices[face.vertex2].data());

			glTexCoord2f(face.tex3s, face.tex3t);
			glVertex3fv(m_vertices[face.vertex3].data());
		}
		glEnd();
	}
}

void Cube::SetTexture(TextureHandle const& texture)
{
	m_texture = texture;
}
