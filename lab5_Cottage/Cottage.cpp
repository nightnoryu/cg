#include "Cottage.h"

Cottage::Cottage()
	: m_section1({ -6, -2, 2 }, 4)
	, m_section2({ -2, -2, 2 }, 4)
	, m_section3({ 2, -1.5f, 2 }, 3)
{
}

void Cottage::Draw() const
{
	m_section1.Draw();
	m_section2.Draw();
	m_section3.Draw();
}

void Cottage::SetWallTexture(TextureHandle const& texture)
{
	m_section1.SetTexture(texture);
}
