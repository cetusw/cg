#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

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

	ShaderProgram(ShaderProgram&& other) noexcept;
	ShaderProgram& operator=(ShaderProgram&& other) noexcept;

	void Use() const;

	void SetIntUniform(const std::string& name, int value);
	void SetFloatUniform(const std::string& name, float value);
	void SetVec2Uniform(const std::string& name, const glm::vec2& value);

private:
	GLint GetUniformLocation(const std::string& name);
	static void CheckLinkStatus(GLuint program);
	void Release() noexcept;

	GLuint m_id{};
	std::unordered_map<std::string, GLint> m_uniformLocations;
};
