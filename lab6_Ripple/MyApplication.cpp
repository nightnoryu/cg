#include "MyApplication.h"
#include "../libgl/TextureLoader.h"
#include "../GlutBase/ShaderLoader.h"

double const MyApplication::ZNEAR = 0.1;
double const MyApplication::ZFAR = 50;
double const MyApplication::FIELD_OF_VIEW = 90;

MyApplication::MyApplication(char const* title, int width, int height)
	: CGLApplication(title, width, height)
{
}

void MyApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);

	gluLookAt(
		0, 0, 3,
		0, 0, 0,
		0, 1, 0);

	InitShaders();
	LoadTextures();
}

void MyApplication::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	m_texture1.Bind();

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	m_texture2.Bind();

	glUseProgram(m_program);

	glUniform1i(m_tex1Location, 0);
	glUniform1i(m_tex2Location, 1);
	glUniform1f(m_timeLocation, m_seconds);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex3f(-2, 2, 0);

		glTexCoord2f(0, 1);
		glVertex3f(-2, -2, 0);

		glTexCoord2f(1, 1);
		glVertex3f(2, -2, 0);

		glTexCoord2f(1, 0);
		glVertex3f(2, 2, 0);
	}
	glEnd();

	glUseProgram(0);
}

void MyApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FIELD_OF_VIEW, aspect, ZNEAR, ZFAR);
	glMatrixMode(GL_MODELVIEW);
}

void MyApplication::OnIdle()
{
	std::chrono::duration<float, std::milli> seconds = std::chrono::high_resolution_clock::now() - m_start;
	m_seconds = seconds.count() / 1000;

	PostRedisplay();
}

void MyApplication::InitShaders()
{
	ShaderLoader loader;
	Shader vertexShader = loader.LoadShader(GL_VERTEX_SHADER, "Shaders/ripple.vsh");
	Shader fragmentShader = loader.LoadShader(GL_FRAGMENT_SHADER, "Shaders/ripple.fsh");

	vertexShader.Compile();
	fragmentShader.Compile();

	m_program.Create();
	m_program.AttachShader(vertexShader);
	m_program.AttachShader(fragmentShader);

	m_program.Link();
	m_start = std::chrono::high_resolution_clock::now();

	m_tex1Location = m_program.GetUniformLocation("tex1");
	m_tex2Location = m_program.GetUniformLocation("tex2");
	m_timeLocation = m_program.GetUniformLocation("time");
}

void MyApplication::LoadTextures()
{
	CTextureLoader loader;
	m_texture1.Attach(loader.LoadTexture2D(L"Textures/tex1.jpg"));
	m_texture2.Attach(loader.LoadTexture2D(L"Textures/tex2.jpg"));
}
