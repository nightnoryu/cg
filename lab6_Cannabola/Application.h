#pragma once

#include "BaseApplication.h"

class Application : public BaseApplication
{
public:
	Application(char const* title);

protected:
	void OnInit() override;
	void OnDisplay() override;
	void OnReshape(int width, int height) override;

private:
	void FillEllipse(float x, float y, float rx, float ry, std::size_t points = 360);
};
