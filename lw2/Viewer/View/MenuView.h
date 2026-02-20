#pragma once
#include <SFML/Graphics.hpp>

class MenuView
{
public:
	enum class MenuAction
	{
		None,
		OpenFile
	};

	MenuView();
	void Draw(sf::RenderWindow& window);
	MenuAction HandleClick(sf::Vector2i mousePos);

private:
	void DrawTopBar(sf::RenderWindow& window);
	void DrawButtons(sf::RenderWindow& window) const;
	void DrawText(sf::RenderWindow& window, const std::string& str, sf::Vector2f textPosition) const;

	static constexpr float TOP_BAR_HEIGHT = 70.f;
	static constexpr float DROPDOWN_WIDTH = 240.f;

	sf::Font m_font;
	sf::RectangleShape m_topBar;
	sf::RectangleShape m_dropdown;
	bool m_isFileMenuOpen = false;
};
