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
	void DispatchEvent(const sf::Event& event) const;

private:
	void HandleMouseClick(const sf::Event::MouseButtonEvent& mouse) const;

	sf::RenderWindow& m_window;

	Image& m_image;
	WindowSettings& m_windowSettings;
	Menu& m_menu;

	ImageController& m_imageController;
};
