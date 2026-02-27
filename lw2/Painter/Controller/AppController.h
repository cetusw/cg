#pragma once

#include "Model/Canvas.h"
#include "View/AppView.h"
#include <SFML/Graphics/RenderWindow.hpp>

class AppController
{
public:
	AppController(sf::RenderWindow& window, Canvas& canvas, AppView& appView);

	void Run();

private:
	sf::RenderWindow& m_window;
	Canvas& m_canvas;
	AppView& m_appView;
	sf::Clock m_deltaTime;

	void HandleEvents();
	void PollEvent() const;
	sf::Vector2f GetCanvasMousePosition() const;
};