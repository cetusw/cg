#pragma once

#include <SFML/Graphics.hpp>
#include "../Model/Image.h"

class ImageView
{
public:
	void UpdateLayout(sf::Vector2u windowSize, sf::Vector2f imageSize);
	void Draw(sf::RenderWindow& window, const Image& image) const;

private:
	static constexpr float VIEWPORT_FULL_SCALE = 1.0f;
	static constexpr float VIEWPORT_START = 0.0f;

	sf::View m_view;
};
