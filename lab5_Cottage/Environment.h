#pragma once

#include "TexturedRectangle.h"

class Environment
{
public:
	Environment();

	void Draw() const;

	void SetGroundTexture(TextureHandle const& texture);

private:
	TexturedRectangle m_ground;
};
