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
	void SetDoorTextures(TextureHandle const& doorTop, TextureHandle const& doorBottom);
	void SetGarageDoorTextures(TextureHandle const& texture);

private:
	TexturedCube m_section1;
	TexturedCube m_section2;
	TexturedCube m_section3;

	TexturedRectangle m_window1;
	TexturedRectangle m_window2;

	TexturedRectangle m_doorTop;
	TexturedRectangle m_doorBottom;

	TexturedRectangle m_garageDoor;
};
