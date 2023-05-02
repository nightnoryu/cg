#pragma once

#include "BaseApplication.h"
#include "ProgramImpl.h"
#include "common_inc.h"

class Application : public BaseApplication
{
public:
	Application(char const* title);

protected:
	void OnInit() override;
	void OnDisplay() override;
	void OnReshape(int width, int height) override;

private:
	void InitShaders();

	Program m_program;
};
