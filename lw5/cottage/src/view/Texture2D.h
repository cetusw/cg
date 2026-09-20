#pragma once

#include <GL/glew.h>

#include <filesystem>

class Texture2D
{
public:
	explicit Texture2D(const std::filesystem::path& path);
	~Texture2D();

	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;
	Texture2D(Texture2D&& other) noexcept;
	Texture2D& operator=(Texture2D&& other) noexcept;

	void Bind() const;

private:
	void Release() noexcept;

	GLuint id{};
};
