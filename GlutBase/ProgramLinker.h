#pragma once

#include "ProgramImpl.h"

class ProgramLinker
{
public:
	void LinkProgram(GLuint program);
	void CheckStatus();

private:
	std::vector<GLuint> m_programs;
};
