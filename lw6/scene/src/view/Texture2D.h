#pragma once

#include <GL/glew.h>

#include <filesystem>

struct ImageData;

class Texture2D
{
public:
	explicit Texture2D(const std::string& path);
	~Texture2D();

	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;
	Texture2D(Texture2D&& other) noexcept;
	Texture2D& operator=(Texture2D&& other) noexcept;

	void Bind() const;

private:
	static void LoadImage(const std::string& path, ImageData& data);
	void CreateTexture(const ImageData& data);
	static void ConfigureParameters();
	static void UploadImage(const ImageData& data, GLenum format);

	void Release() noexcept;

	GLuint m_id{};
};
