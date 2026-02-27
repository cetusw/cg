#pragma once

#include "../Model/Image.h"
#include "Observer/IObserver.h"
#include <SFML/Graphics.hpp>

class ImageView final : public IObserver
{
public:
	void Draw(sf::RenderWindow& window, const Image& image);
	void OnModelChanged() override;

private:
	static constexpr float VIEWPORT_FULL_SCALE = 1.0f;
	static constexpr float VIEWPORT_START = 0.0f;

	sf::View m_view;
	bool m_needsUpdate = false;

	void UpdateLayout(sf::Vector2u windowSize, sf::Vector2f imageSize);
};
