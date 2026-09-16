#include "Image.h"

bool Image::LoadImage(const std::string& filename)
{
	if (!m_image.loadFromFile(filename))
	{
		return false;
	}
	m_viewCenter = static_cast<sf::Vector2f>(m_image.getSize()) / 2.f;
	Notify();
	return true;
}

bool Image::IsLoaded() const
{
	return m_image.getSize().x > 0;
}

bool Image::Contains(const sf::Vector2f mousePosition) const
{
	if (!IsLoaded())
	{
		return false;
	}

	const sf::Vector2f size = GetSize();
	return mousePosition.x >= 0
		&& mousePosition.x < size.x
		&& mousePosition.y >= 0
		&& mousePosition.y < size.y;
}

sf::Vector2f Image::TransformPixelToWorld(const sf::Vector2i pixel, const sf::Vector2u windowSize) const
{
	const sf::Vector2f offsetFromWindowCenter = static_cast<sf::Vector2f>(pixel) - (static_cast<sf::Vector2f>(windowSize) / 2.f);

	return m_viewCenter + offsetFromWindowCenter;
}

const sf::Texture& Image::GetTexture() const
{
	return m_image;
}

sf::Vector2f Image::GetSize() const
{
	return static_cast<sf::Vector2f>(m_image.getSize());
}

void Image::SetViewCenter(const sf::Vector2f center)
{
	m_viewCenter = center;
	Notify();
}

sf::Vector2f Image::GetViewCenter() const
{
	return m_viewCenter;
}
