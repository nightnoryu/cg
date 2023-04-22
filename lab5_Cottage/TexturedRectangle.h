#pragma once

#include "TextureHandle.h"

class TexturedRectangle
{
public:
	TexturedRectangle(glm::vec3 position, glm::vec3 direction1, glm::vec3 direction2);

	void Draw() const;

	void SetTexture(TextureHandle texture);

private:
	glm::vec3 m_position = { 0, 0, 0 };
	glm::vec3 m_direction1 = { 1, 0, 0 };
	glm::vec3 m_direction2 = { 0, 1, 0 };

	TextureHandle m_texture;
};
