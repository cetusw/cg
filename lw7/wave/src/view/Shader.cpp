#include "view/Shader.h"

#include <fstream>
#include <iterator>
#include <stdexcept>
#include <utility>

Shader::Shader(const GLenum type, const std::filesystem::path& path)
	: m_id(Compile(type, ReadSource(path)))
	, m_path(path)
{
}

Shader::~Shader()
{
	Release();
}

Shader::Shader(Shader&& other) noexcept
	: m_id(std::exchange(other.m_id, 0))
{
}

Shader& Shader::operator=(Shader&& other) noexcept
{
	if (this != &other)
	{
		Release();
		m_id = std::exchange(other.m_id, 0);
	}
	return *this;
}

GLuint Shader::GetId() const
{
	return m_id;
}

std::string Shader::ReadSource(const std::filesystem::path& path)
{
	std::ifstream file(path, std::ios::binary); // TODO уточнить что значит std::ios::binary
	if (!file)
	{
		throw std::runtime_error("Failed to read shader: " + path.string());
	}
	return { std::istreambuf_iterator(file), std::istreambuf_iterator<char>() }; // TODO что здесь происходит
}

GLuint Shader::Compile(const GLenum type, const std::string& source) const
{
	const GLuint shader = glCreateShader(type);
	if (shader == 0)
	{
		throw std::runtime_error("Failed to create shader: " + m_path.string());
	}

	try
	{
		const char* sourceData = source.c_str();
		glShaderSource(shader, 1, &sourceData, nullptr);
		glCompileShader(shader);
		return CheckCompileStatus(shader);
	}
	catch (...)
	{
		glDeleteShader(shader);
		throw;
	}
}

GLuint Shader::CheckCompileStatus(const GLuint shader) const
{
	GLint wasCompiled = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &wasCompiled);
	if (wasCompiled == GL_TRUE)
	{
		return shader;
	}

	GLint logLength = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	std::string log(static_cast<std::size_t>(logLength), '\0');
	GLsizei writtenLength = 0;
	glGetShaderInfoLog(shader, logLength, &writtenLength, log.data());
	log.resize(static_cast<std::size_t>(writtenLength));
	throw std::runtime_error("Failed to compile shader: " + m_path.string() + "\n\n" + log);
}

void Shader::Release() noexcept
{
	if (m_id != 0)
	{
		glDeleteShader(m_id);
		m_id = 0;
	}
}
