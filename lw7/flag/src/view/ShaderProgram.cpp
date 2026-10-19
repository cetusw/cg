#include "view/ShaderProgram.h"

#include "view/Shader.h"

#include <stdexcept>

ShaderProgram::ShaderProgram(
	const std::filesystem::path& vertexShaderPath,
	const std::filesystem::path& fragmentShaderPath)
{
	const Shader vertexShader(GL_VERTEX_SHADER, vertexShaderPath);
	const Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

	m_id = glCreateProgram();
	if (m_id == 0)
	{
		throw std::runtime_error("Failed to create shader program");
	}
	glAttachShader(m_id, vertexShader.GetId());
	glAttachShader(m_id, fragmentShader.GetId());
	glLinkProgram(m_id);
	CheckLinkStatus(m_id);
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
	glGetProgramInfoLog(program, logLength, nullptr, log.data());
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
