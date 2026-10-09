#pragma once

#include <GL/glew.h>

#include <filesystem>
#include <string>

class Shader
{
public:
	Shader(GLenum type, const std::filesystem::path& path);
	~Shader();

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

	[[nodiscard]] GLuint GetId() const;

private:
	static std::string ReadSource(const std::filesystem::path& path);
	[[nodiscard]] GLuint Compile(GLenum type, const std::string& source) const;
	[[nodiscard]] GLuint CheckCompileStatus(GLuint shader) const;
	void Release() noexcept;

	GLuint m_id{};
	std::filesystem::path m_path{};
};
