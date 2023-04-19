#include "Cuboid.h"

void Cuboid::Draw() const
{
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
