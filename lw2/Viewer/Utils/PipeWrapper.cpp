#include "PipeWrapper.h"

#include <stdio.h>

PipeWrapper::PipeWrapper(const char* command, const char* mode)
{
	m_pipe = popen(command, mode);
}

PipeWrapper::~PipeWrapper()
{
	if (IsOpen())
	{
		pclose(m_pipe);
	}
}

FILE* PipeWrapper::Get() const
{
	return m_pipe;
}

bool PipeWrapper::IsOpen() const
{
	return m_pipe != nullptr;
}