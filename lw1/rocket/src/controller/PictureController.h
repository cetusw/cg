#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "DragController.h"
#include "../model/Picture.h"

class PictureController
{
public:
	explicit PictureController(Picture& picture);

	void HandleEvent(const sf::Event& event, const sf::RenderWindow& window);

private:
	void HandleMouseButtonPressed(const sf::Event& event, const sf::RenderWindow& window);
	void HandleMouseMoved(const sf::Event& event, const sf::RenderWindow& window) const;
	void HandleMouseReleased(const sf::Event& event);
	void HandleFocusLost(const sf::Event& event);

	[[nodiscard]] static sf::Vector2f GetMousePosition(
		const sf::Vector2i& pixelPosition,
		const sf::RenderWindow& window);

	Picture& m_picture;
	DragController m_dragController;
};
