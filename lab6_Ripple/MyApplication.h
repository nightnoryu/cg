#pragma once

#include "../libgl/GLApplication.h"
#include "../libgl/Texture.h"
#include "common_inc.h"
#include "../GlutBase/ProgramImpl.h"

class MyApplication : public CGLApplication
{
public:
	MyApplication(char const* title, int width, int height);

protected:
	void OnInit() override;
	void OnDisplay() override;
	void OnReshape(int width, int height) override;
	void OnIdle() override;

private:
	static double const FIELD_OF_VIEW;

	static double const ZNEAR;
	static double const ZFAR;

	void InitShaders();
	void LoadTextures();

	Program m_program;
	GLint m_tex1Location = 0;
	GLint m_tex2Location = 0;
	GLint m_timeLocation = 0;

	CTexture2D m_texture1;
	CTexture2D m_texture2;

	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	float m_seconds = 0;
};