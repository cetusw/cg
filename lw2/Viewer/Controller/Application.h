#pragma once

#include "../Model/Image.h"
#include "../Model/ViewerSettings.h"
#include "../View/BackgroundView.h"
#include "../View/ImageView.h"
#include "../View/MenuView.h"
#include <SFML/Graphics.hpp>

class Application
{
public:
	Application();
	void Run();

private:
	void HandleEvents();
	void HandleClick(const sf::Event& event);
	void OpenFileDialog();
	void UpdateLayouts();

	sf::RenderWindow m_window;
	Image m_image;
	ImageView m_imageView;
	MenuView m_menuView;
	ViewerSettings m_settings;
	BackgroundView m_backgroundView;
};
