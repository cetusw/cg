#pragma once

#include "Controller/AppController.h"
#include "Controller/ImageController.h"
#include "Model/Image.h"
#include "Model/WindowSettings.h"
#include "View/BackgroundView.h"
#include "View/ImageView.h"
#include "View/MenuView.h"
#include <SFML/Graphics.hpp>

class Application
{
public:
	Application();
	void Run();

private:
	sf::RenderWindow m_window;

	Image m_image;
	WindowSettings m_windowSettings;
	Menu m_menu;

	ImageController m_imageController;
	AppController m_appController;

	ImageView m_imageView;
	MenuView m_menuView;
	BackgroundView m_backgroundView;
};
