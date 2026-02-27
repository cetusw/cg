#pragma once

#include <SFML/Graphics.hpp>

class BackgroundView
{
public:
	BackgroundView();
	void Draw(sf::RenderWindow& window) const;

private:
	sf::Texture m_texture;
};
