#pragma once

#include "TexturedCube.h"
#include "TexturedRectangle.h"

class Cottage
{
public:
	Cottage();

	void Draw() const;

	void SetWallTexture(TextureHandle const& texture);
	void SetWindowTexture(TextureHandle const& texture);

private:
	TexturedCube m_section1;
	TexturedCube m_section2;
	TexturedCube m_section3;

	TexturedRectangle m_window1;
	TexturedRectangle m_window2;
};
