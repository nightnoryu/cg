#include "pch.h"
#include "ProgramLinker.h"

void ProgramLinker::LinkProgram(GLuint program)
{
	ProgramHandle handle(program);
	handle.Link();

	if (handle.GetParameter(GL_LINK_STATUS) != GL_TRUE)
	{
		std::stringstream message;
		message << "Program " << handle << " linkage failed: " << handle.GetInfoLog();

		throw std::runtime_error(message.str());
	}
}
