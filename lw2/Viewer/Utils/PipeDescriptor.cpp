#include "PipeDescriptor.h"

#include <stdio.h>

PipeDescriptor::PipeDescriptor(const char* command, const char* mode)
{
	m_pipe = popen(command, mode);
}

PipeDescriptor::~PipeDescriptor()
{
	if (IsOpen())
	{
		pclose(m_pipe);
	}
}

FILE* PipeDescriptor::Get() const
{
	return m_pipe;
}

bool PipeDescriptor::IsOpen() const
{
	return m_pipe != nullptr;
}