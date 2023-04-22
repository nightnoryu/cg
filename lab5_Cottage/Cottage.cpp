#include "Cottage.h"

Cottage::Cottage()
	: m_section1({ -6, -2, 2 }, 4)
	, m_section2({ -2, -2, 2 }, 4)
	, m_section3({ 2, -1.5f, 2 }, 3)
	, m_window1({ -0.5f, -2.1f, 4 }, { 1, 0, 0 }, { 0, 0, -1 })
	, m_window2({ -4.5f, -2.1f, 4 }, { 1, 0, 0 }, { 0, 0, -1 })
	, m_doorTop({ -2.5f, -2.1f, 4 }, { 1, 0, 0 }, { 0, 0, -1 })
	, m_doorBottom({ -2.5f, -2.1f, 3 }, { 1, 0, 0 }, { 0, 0, -1 })
	, m_garageDoor({ 2.3f, -1.6f, 4.5f }, { 2.2f, 0, 0 }, { 0, 0, -2.5f })
{
}

void Cottage::Draw() const
{
	m_section1.Draw();
	m_section2.Draw();
	m_section3.Draw();

	m_window1.Draw();
	m_window2.Draw();

	m_doorTop.Draw();
	m_doorBottom.Draw();

	m_garageDoor.Draw();
}

void Cottage::SetWallTexture(TextureHandle const& texture)
{
	m_section1.SetTexture(texture);
}

void Cottage::SetWindowTexture(TextureHandle const& texture)
{
	m_window1.SetTexture(texture);
}

void Cottage::SetDoorTextures(TextureHandle const& doorTop, TextureHandle const& doorBottom)
{
	m_doorTop.SetTexture(doorTop);
	m_doorBottom.SetTexture(doorBottom);
}

void Cottage::SetGarageDoorTextures(TextureHandle const& texture)
{
	m_garageDoor.SetTexture(texture);
}
