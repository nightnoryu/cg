#include "pch.h"
#include "ProgramLinker.h"

void ProgramLinker::LinkProgram(GLuint program)
{
	ProgramHandle handle(program);
	handle.Link();
	m_programs.push_back(program);
}

void ProgramLinker::CheckStatus()
{
	std::stringstream strm;

	bool hasErrors = false;

	for (auto&& program : m_programs)
	{
		ProgramHandle handle(program);
		if (handle.GetParameter(GL_LINK_STATUS) != GL_TRUE)
		{
			hasErrors = true;
			strm << "Program " << handle << " linkage failed: " << handle.GetInfoLog() << "\n";
		}
	}

	m_programs.clear();

	if (hasErrors)
	{
		throw std::runtime_error(strm.str());
	}
}
