#include "view/ShaderProgram.h"

#include "view/Shader.h"

#include <stdexcept>
#include <utility>

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

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
	: m_id(std::exchange(other.m_id, 0))
	, m_uniformLocations(std::move(other.m_uniformLocations))
{
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
	if (this != &other)
	{
		Release();
		m_id = std::exchange(other.m_id, 0);
		m_uniformLocations = std::move(other.m_uniformLocations);
	}
	return *this;
}

void ShaderProgram::Use() const
{
	glUseProgram(m_id);
}

void ShaderProgram::SetIntUniform(const std::string& name, const int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetFloatUniform(const std::string& name, const float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void ShaderProgram::SetVec2Uniform(const std::string& name, const glm::vec2& value)
{
	glUniform2f(GetUniformLocation(name), value.x, value.y);
}

GLint ShaderProgram::GetUniformLocation(const std::string& name)
{
	const auto iterator = m_uniformLocations.find(name);
	if (iterator != m_uniformLocations.end())
	{
		return iterator->second;
	}

	const GLint location = glGetUniformLocation(m_id, name.c_str());
	if (location == -1)
	{
		throw std::runtime_error("Failed to find uniform: " + name);
	}
	m_uniformLocations.emplace(name, location);
	return location;
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
