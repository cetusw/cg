#pragma once

#include <GL/glew.h>

#include <filesystem>

class ShaderProgram
{
public:
	ShaderProgram(
		const std::filesystem::path& vertexShaderPath,
		const std::filesystem::path& fragmentShaderPath);
	~ShaderProgram();

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;

	void Use() const;

private:
	static void CheckLinkStatus(GLuint program);
	void Release() noexcept;

	GLuint m_id{};
};
