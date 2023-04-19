#pragma once

#include "Cuboid.h"

class Cottage
{
public:
	void Draw() const;

	void SetWallTexture(TextureHandle const& texture);

private:
	Cuboid m_section1;
	Cuboid m_section2;
	Cuboid m_section3;
};
