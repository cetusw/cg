#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "view/Texture2D.h"

#include <stdexcept>
#include <utility>

namespace
{
GLenum GetFormat(const int channels)
{
	switch (channels)
	{
	case 1:
		return GL_RED; // TODO разобраться с этим форматом
	case 3:
		return GL_RGB;
	case 4:
		return GL_RGBA;
	default:
		throw std::runtime_error("Unsupported texture channel count");
	}
}
} // namespace

Texture2D::Texture2D(const std::filesystem::path& path)
{
	int width{};
	int height{};
	int channels{};
	stbi_uc* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
	if (data == nullptr)
	{
		throw std::runtime_error("Failed to load texture: " + path.string());
	}

	try
	{
		const GLenum format = GetFormat(channels);
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), width, height, 0, format, GL_UNSIGNED_BYTE, data);
	}
	catch (...)
	{
		stbi_image_free(data);
		Release();
		throw;
	}

	stbi_image_free(data);
}

Texture2D::~Texture2D() { Release(); }

Texture2D::Texture2D(Texture2D&& other) noexcept
	: id(std::exchange(other.id, 0))
{
}

Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
{
	if (this != &other)
	{
		Release();
		id = std::exchange(other.id, 0);
	}
	return *this;
}

void Texture2D::Bind() const { glBindTexture(GL_TEXTURE_2D, id); }

void Texture2D::Release() noexcept
{
	if (id != 0)
	{
		glDeleteTextures(1, &id);
		id = 0;
	}
}
