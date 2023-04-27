#pragma once

#include "common_inc.h"

class ProgramBase
{
public:
	void AttachShader(GLuint shader);
	void DetachShader(GLuint shader);

	void Link() const;
	void Validate() const;

	GLuint Attach(GLuint program);
	GLuint Detach();

	void Delete();

	operator GLuint() const;

	GLint GetParameter(GLenum name);

	std::string GetInfoLog();

protected:
	ProgramBase(GLuint program = 0);

	~ProgramBase() = default;

private:
	GLuint m_program;
};
