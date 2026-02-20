#include "Image.h"

bool Image::LoadImage(const std::string& filename)
{
	return m_image.loadFromFile(filename);
}

bool Image::IsLoaded() const
{
	return m_image.getSize().x > 0;
}

const sf::Texture& Image::GetTexture() const
{
	return m_image;
}

sf::Vector2f Image::GetSize() const
{
	return static_cast<sf::Vector2f>(m_image.getSize());
}