#pragma once

#include <cstdio>

class PipeDescriptor
{
public:
	PipeDescriptor(const char* command, const char* mode);
	~PipeDescriptor();

	PipeDescriptor(const PipeDescriptor&) = delete;
	PipeDescriptor& operator=(const PipeDescriptor&) = delete;

	FILE* Get() const;
	bool IsOpen() const;

private:
	FILE* m_pipe;
};
