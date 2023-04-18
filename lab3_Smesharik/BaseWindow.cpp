#include "BaseWindow.h"

BaseWindow::BaseWindow(int width, int height, std::string const& title)
	: m_window{ MakeWindow(width, height, title.c_str()) }
{
	if (!m_window)
	{
		throw std::runtime_error("Failed to create window");
	}

	glfwSetWindowUserPointer(m_window, this);

	glfwSetWindowSizeCallback(
		m_window,
		[](GLFWwindow* window, int width, int height) {
			GetBaseWindow(window)->OnResize(width, height);
		});
}

BaseWindow::~BaseWindow() noexcept
{
	glfwDestroyWindow(m_window);
}

void BaseWindow::Run()
{
	glfwMakeContextCurrent(m_window);
	OnRunStart();

	{
		auto const size = GetFrameBufferSize();
		OnResize(size.x, size.y);
	}

	while (!glfwWindowShouldClose(m_window))
	{
		auto const size = GetFrameBufferSize();
		Draw(size.x, size.y);
		glFinish();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	OnRunEnd();
}

BaseWindow* BaseWindow::GetBaseWindow(GLFWwindow* window)
{
	return reinterpret_cast<BaseWindow*>(glfwGetWindowUserPointer(window));
}

GLFWwindow* BaseWindow::MakeWindow(int width, int height, char const* title)
{
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_SAMPLES, 32);
	return glfwCreateWindow(width, height, title, nullptr, nullptr);
}

glm::ivec2 BaseWindow::GetFrameBufferSize() const
{
	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);
	return { width, height };
}
