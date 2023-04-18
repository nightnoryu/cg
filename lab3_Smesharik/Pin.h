#pragma once

#include "common_inc.h"

class Pin
{
public:
	void Draw() const;

private:
	void DrawBody() const;
	void DrawEyes() const;
	void DrawBeak() const;
	void DrawLegs() const;
	void DrawArms() const;
	void DrawHat() const;

	const glm::vec3 RED = { 0xe3 / 255.0f, 0, 0x1b / 255.0f };
	const glm::vec3 PRIMARY_BROWN = { 0xae / 255.0f, 0x6f / 255.0f, 0x08 / 255.0f };
	const glm::vec3 SECONDARY_BROWN = { 0x80 / 255.0f, 0x26 / 255.0f, 0x25 / 255.0f };
	const glm::vec3 GREY = { 0xe3 / 255.0f, 0xe4 / 255.0f, 0xe6 / 255.0f };
};
