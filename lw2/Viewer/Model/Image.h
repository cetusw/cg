#pragma once

#include "Observable/Observable.h"
#include <SFML/Graphics.hpp>
#include <string>

class Image : public Observable
{
public:
	bool LoadImage(const std::string& filename);
	bool IsLoaded() const;
	bool Contains(sf::Vector2f mousePosition) const;
	sf::Vector2f TransformPixelToWorld(sf::Vector2i pixel, sf::Vector2u windowSize) const;

	const sf::Texture& GetTexture() const;
	sf::Vector2f GetSize() const;
	sf::Vector2f GetViewCenter() const;

	void SetViewCenter(sf::Vector2f center);

private:
	sf::Texture m_image;
	sf::Vector2f m_viewCenter{ 0.f, 0.f };
};
