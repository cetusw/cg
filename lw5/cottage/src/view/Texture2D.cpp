#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "view/Texture2D.h"

#include <stdexcept>
#include <utility>

struct ImageData
{
	int width{};
	int height{};
	int channels{};
	stbi_uc* pixels{};
};

namespace
{
GLenum GetFormat(const int channels)
{
	switch (channels)
	{
	case 3:
		return GL_RGB;
	case 4:
		return GL_RGBA;
	default:
		throw std::runtime_error("Unsupported texture channel count");
	}
}
} // namespace

Texture2D::Texture2D(const std::string& path)
{
	ImageData data;
	LoadImage(path, data);

	try
	{
		CreateTexture(data);
	}
	catch (...)
	{
		stbi_image_free(data.pixels);
		Release();
		throw;
	}

	stbi_image_free(data.pixels);
}

Texture2D::~Texture2D()
{
	Release();
}

Texture2D::Texture2D(Texture2D&& other) noexcept
	: m_id(std::exchange(other.m_id, 0))
{
}

Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
{
	if (this != &other)
	{
		Release();
		m_id = std::exchange(other.m_id, 0);
	}
	return *this;
}

void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture2D::LoadImage(const std::string& path, ImageData& data)
{
	data.pixels = stbi_load(
		path.c_str(),
		&data.width,
		&data.height,
		&data.channels,
		0);

	if (data.pixels == nullptr)
	{
		throw std::runtime_error("Failed to load texture: " + path);
	}
}

void Texture2D::CreateTexture(const ImageData& data)
{
	const GLenum format = GetFormat(data.channels);

	glGenTextures(1, &m_id);
	Bind();

	ConfigureParameters();
	UploadImage(data, format);
}

void Texture2D::ConfigureParameters()
{
	// TODO запомнить значения параметров
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);

	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);

	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_S,
		GL_REPEAT);

	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_T,
		GL_REPEAT);
}

void Texture2D::UploadImage(const ImageData& data, const GLenum format)
{
	constexpr int mipmapLevel = 0;
	constexpr int borderSize = 0;
	glTexImage2D(
		GL_TEXTURE_2D,
		mipmapLevel,
		static_cast<GLint>(format),
		data.width,
		data.height,
		borderSize,
		format,
		GL_UNSIGNED_BYTE,
		data.pixels);
}

void Texture2D::Release() noexcept
{
	if (m_id != 0)
	{
		glDeleteTextures(1, &m_id);
		m_id = 0;
	}
}
