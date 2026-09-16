#pragma once

#include "../Model/Image.h"
#include "../Model/WindowSettings.h"
#include "../View/ImageView.h"
#include "../View/MenuView.h"
#include "ImageController.h"

class AppController
{
public:
	AppController(
		Image& image,
		ImageController& imageController,
		WindowSettings& windowSettings,
		Menu& menu,
		sf::RenderWindow& window);
	void DispatchEvent(const sf::Event& event);

private:
	void HandleMouseClick(const sf::Event::MouseButtonEvent& mouse);
	void HandleMouseRelease(const sf::Event::MouseButtonEvent& mouse);
	void HandleMouseMove(const sf::Event::MouseMoveEvent& mouse);

	sf::RenderWindow& m_window;

	Image& m_image;
	WindowSettings& m_windowSettings;
	Menu& m_menu;

	ImageController& m_imageController;

	bool m_isDragging = false;
	sf::Vector2i m_lastMousePos;
};
