#pragma once

#include "common_inc.h"

class BaseWindow
{
public:
	BaseWindow(int width, int height, std::string const& title);

	BaseWindow(BaseWindow const&) = delete;
	BaseWindow& operator=(BaseWindow const&) = delete;

	virtual ~BaseWindow() noexcept;

	void Run();

private:
	static BaseWindow* GetBaseWindow(GLFWwindow* window);
	static GLFWwindow* MakeWindow(int width, int height, char const* title);

	glm::ivec2 GetFrameBufferSize() const;

	virtual void OnResize(int width, int height) {};
	virtual void OnRunStart() {};
	virtual void OnRunEnd() {};

	virtual void Draw(int width, int height) = 0;

	GLFWwindow* m_window;
};
