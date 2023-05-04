#pragma once

#include "ProgramImpl.h"

class ProgramLinker // TODO: strange architecture
{
public:
	void LinkProgram(GLuint program);
	void CheckStatus();

private:
	std::vector<GLuint> m_programs;
};
