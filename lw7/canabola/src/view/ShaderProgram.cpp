#include "view/ShaderProgram.h"

#include "view/Shader.h"

#include <stdexcept>
#include <string>

ShaderProgram::ShaderProgram(
	const std::filesystem::path& vertexShaderPath,
	const std::filesystem::path& fragmentShaderPath)
{
	const Shader vertexShader(GL_VERTEX_SHADER, vertexShaderPath);
	const Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

	const GLuint program = glCreateProgram();
	if (program == 0)
	{
		throw std::runtime_error("Failed to create shader program");
	}

	try
	{
		glAttachShader(program, vertexShader.GetId());
		glAttachShader(program, fragmentShader.GetId());
		glLinkProgram(program);
		CheckLinkStatus(program);
		glDetachShader(program, vertexShader.GetId());
		glDetachShader(program, fragmentShader.GetId());
		m_id = program;
	}
	catch (...)
	{
		glDeleteProgram(program);
		throw;
	}
}

ShaderProgram::~ShaderProgram()
{
	Release();
}

void ShaderProgram::Use() const
{
	glUseProgram(m_id);
}

void ShaderProgram::CheckLinkStatus(const GLuint program)
{
	GLint wasLinked = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &wasLinked);
	if (wasLinked == GL_TRUE)
	{
		return;
	}

	GLint logLength = 0;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	std::string log(static_cast<std::size_t>(logLength), '\0');
	GLsizei writtenLength = 0;
	glGetProgramInfoLog(program, logLength, &writtenLength, log.data());
	log.resize(static_cast<std::size_t>(writtenLength));
	throw std::runtime_error("Failed to link shader program:\n\n" + log);
}

void ShaderProgram::Release() noexcept
{
	if (m_id != 0)
	{
		glDeleteProgram(m_id);
		m_id = 0;
	}
}
