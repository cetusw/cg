#pragma once

#include "Observable/Observable.h"
#include <SFML/Graphics.hpp>
#include <string>

class Image : public Observable
{
public:
	bool LoadImage(const std::string& filename);
	bool IsLoaded() const;
	const sf::Texture& GetTexture() const;
	sf::Vector2f GetSize() const;

private:
	sf::Texture m_image;
};
