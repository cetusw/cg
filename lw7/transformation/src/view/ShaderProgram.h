#pragma once

#include <GL/glew.h>

#include <filesystem>
#include <string>
#include <unordered_map>

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
	void SetFloatUniform(const std::string& name, float value);

private:
	GLint GetUniformLocation(const std::string& name);
	static void CheckLinkStatus(GLuint program);
	void Release() noexcept;

	GLuint m_id = 0;
	std::unordered_map<std::string, GLint> m_uniformLocations;
};
