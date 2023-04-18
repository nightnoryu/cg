#pragma once

#include "common_inc.h"

class BaseWindow
{
public:
	BaseWindow(int w, int h, char const* title);

	BaseWindow(BaseWindow const&) = delete;
	BaseWindow& operator=(BaseWindow const&) = delete;

	virtual ~BaseWindow();

	glm::ivec2 GetFramebufferSize() const;

	void Run();

	glm::dvec2 GetCursorPos() const;

private:
	static BaseWindow* GetBaseWindow(GLFWwindow* window);

	virtual void OnResize(
		[[maybe_unused]] int width, [[maybe_unused]] int height) {}
	virtual void OnMouseButton(
		[[maybe_unused]] int button, [[maybe_unused]] int action,
		[[maybe_unused]] int mods) {}
	virtual void OnMouseMove(
		[[maybe_unused]] double x, [[maybe_unused]] double y) {}
	virtual void Draw(int width, int height) = 0;
	virtual void OnRunStart() {}
	virtual void OnRunEnd() {}

	static GLFWwindow* MakeWindow(int w, int h, char const* title);

	GLFWwindow* m_window;
};
