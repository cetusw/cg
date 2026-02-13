#ifndef LETTERS_SIMULATION_H
#define LETTERS_SIMULATION_H

#include "../Model/Letter.h"
#include <SFML/Graphics.hpp>

class Simulation
{
public:
	Simulation();
	void Run();

private:
	sf::RenderWindow m_window;
	std::vector<Letter> m_letters;
	sf::Clock m_clock;

	void SetupLetters();
	void ProcessEvents();
	void Update(float deltaTime);
	void Render();
};

#endif // LETTERS_SIMULATION_H
