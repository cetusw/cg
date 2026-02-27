#pragma once

#include "../Model/Menu.h"
#include <SFML/Graphics.hpp>

class MenuView final : public IObserver
{
public:
	MenuView();
	void Draw(sf::RenderWindow& window, const Menu& menu);
	void OnModelChanged() override;

private:
	void DrawText(sf::RenderWindow& window, const std::string& str, sf::Vector2f textPosition);
	void UpdateLayout(const sf::RenderWindow& window, const Menu& menu);

	sf::Font m_font;
	sf::RectangleShape m_topBar;
	sf::RectangleShape m_dropdown;
	sf::Text m_text;
	bool m_needsUpdate = true;
};
