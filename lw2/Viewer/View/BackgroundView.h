#pragma once

#include "../Model/ViewerSettings.h"
#include <SFML/Graphics.hpp>

class BackgroundView
{
public:
	BackgroundView();
	void Draw(sf::RenderWindow& window, const ViewerSettings& settings) const;

private:
	sf::Texture m_texture;
};
