#pragma once

#include <cstdio>

class PipeWrapper {
public:
	PipeWrapper(const char* command, const char* mode);
	~PipeWrapper();

	PipeWrapper(const PipeWrapper&) = delete;
	PipeWrapper& operator=(const PipeWrapper&) = delete;

	FILE* Get() const;
	bool IsOpen() const;

private:
	FILE* m_pipe;
};
