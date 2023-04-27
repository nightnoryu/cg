#pragma once

#include "BaseWindow.h"
#include "ProgramImpl.h"

class Window : public BaseWindow
{
public:
	Window(int w, int h, char const* title);

private:
	void OnResize(int width, int height) override;
	void OnRunStart() override;

	void InitShaders();

	void Draw(int width, int height) const override;

	void SetupCameraMatrix() const;

	Program m_program;
};
