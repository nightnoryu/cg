#pragma once

#include "TextureHandle.h"

class Cuboid
{
public:
	void Draw() const;

	void SetStartingPoint(glm::vec3 point);
	void SetDimensions(glm::vec3 dimensions);
	void SetTexture(TextureHandle const& texture);

private:
	glm::vec3 m_startingPoint = { 0, 0, 0 };
	glm::vec3 m_dimensions = { 5, 5, 5 };
	TextureHandle m_texture;
};
