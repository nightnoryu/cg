#include "TexturedRectangle.h"

TexturedRectangle::TexturedRectangle(glm::vec3 position, glm::vec3 direction1, glm::vec3 direction2)
	: m_position(position)
	, m_direction1(direction1)
	, m_direction2(direction2)
{
}

void TexturedRectangle::Draw() const
{
	m_texture.Bind();

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex3fv(glm::value_ptr(m_position));

		glTexCoord2f(0, m_textureScale);
		glVertex3fv(glm::value_ptr(m_position + m_direction2));
		
		glTexCoord2f(m_textureScale, m_textureScale);
		glVertex3fv(glm::value_ptr(m_position + m_direction1 + m_direction2));

		glTexCoord2f(m_textureScale, 0);
		glVertex3fv(glm::value_ptr(m_position + m_direction1));
	}
	glEnd();
}

void TexturedRectangle::SetTexture(TextureHandle texture)
{
	m_texture = texture;
}

void TexturedRectangle::SetTextureScale(float scale)
{
	m_textureScale = scale;
}
