#pragma once

#include "BaseWindow.h"
#include "Pin.h"

class Window : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	void OnResize(int width, int height) override;
	void OnRunStart() override;

	void Draw(int width, int height) override;

	static void SetupProjectionMatrix(int width, int height);

	Pin m_pin;
};
