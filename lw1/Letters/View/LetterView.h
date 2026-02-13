#ifndef LETTERS_LETTERVIEW_H
#define LETTERS_LETTERVIEW_H

#include "../Model/Letter.h"
#include <SFML/Graphics/RenderWindow.hpp>

class LetterView
{
public:
	static void Render(sf::RenderWindow& window, const Letter& letter);

private:
	static sf::Vector2f CalculateGlobalPosition(sf::Vector2f letterPosition, sf::Vector2f partPosition);
};

#endif // LETTERS_LETTERVIEW_H