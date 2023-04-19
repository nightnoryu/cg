#include "Cottage.h"

void Cottage::Draw() const
{
	m_section1.Draw();
	m_section2.Draw();
	m_section3.Draw();
}

void Cottage::SetWallTexture(TextureHandle const& texture)
{
	m_section1.SetTexture(texture);
	m_section2.SetTexture(texture);
	m_section3.SetTexture(texture);
}
