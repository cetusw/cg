#include "Controller/AppController.h"
#include "Model/Canvas.h"
#include "View/AppView.h"

#include <SFML/Graphics/RenderWindow.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Painter");
	window.setFramerateLimit(60);

	Canvas canvas(sf::Vector2u(1920, 1080));
	AppView view(window, canvas);
	AppController controller(window, canvas, view);

	controller.Run();

	return 0;
}