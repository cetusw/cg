#pragma once

#include <GL/glew.h>

#include <filesystem>

struct ImageData;

class Texture2D
{
public:
	explicit Texture2D(const std::string& path);
	Texture2D(int width, int height);
	~Texture2D();

	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;
	Texture2D(Texture2D&& other) noexcept;
	Texture2D& operator=(Texture2D&& other) noexcept;

	void Bind() const;
	void Resize(int width, int height) const;
	[[nodiscard]] GLuint GetId() const;

private:
	static void LoadImage(const std::string& path, ImageData& data);
	void CreateTexture(const ImageData& data);
	static void ConfigureImageParameters();
	static void ConfigureRenderTargetParameters();
	static void UploadImage(const ImageData& data);
	void CreateRenderTarget(int width, int height);

	void Release() noexcept;

	GLuint m_id{};
};
