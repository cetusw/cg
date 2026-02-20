#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Image
{
public:
	bool LoadImage(const std::string& filename);
	bool IsLoaded() const;
	const sf::Texture& GetTexture() const;
	sf::Vector2f GetSize() const;

private:
	sf::Texture m_image;
};
