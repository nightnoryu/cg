#pragma once

#include "Cube.h"

class Cottage
{
public:
	Cottage();

	void Draw() const;

	void SetWallTexture(TextureHandle const& texture);

private:
	Cube m_section1;
	Cube m_section2;
	Cube m_section3;
};
