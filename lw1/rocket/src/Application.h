#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "controller/PictureController.h"
#include "model/Rocket.h"
#include "view/PictureView.h"

class Application
{
public:
	Application();

	void Run();

private:
	void ProcessEvents();

	void Render();

	sf::RenderWindow m_window;
	Rocket m_rocket;
	PictureView m_pictureView;
	PictureController m_pictureController;
};
