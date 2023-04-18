#pragma once

#include "common_inc.h"

class GLFWInitializer final
{
public:
	GLFWInitializer();

	GLFWInitializer(GLFWInitializer const&) = delete;
	GLFWInitializer& operator=(GLFWInitializer const&) = delete;

	~GLFWInitializer() noexcept;
};
