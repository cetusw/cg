#include "MenuView.h"

MenuView::MenuView()
{
	if (!m_font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf"))
	{
		throw std::runtime_error("Failed to load font");
	}
	m_topBar.setFillColor(sf::Color(45, 45, 45));
	m_dropdown.setFillColor(sf::Color(70, 70, 70));
	m_dropdown.setOutlineThickness(1);
	m_dropdown.setOutlineColor(sf::Color(35, 35, 35));
}

void MenuView::Draw(sf::RenderWindow& window)
{
	const sf::View uiView(sf::FloatRect(0.f, 0.f,
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)));

	window.setView(uiView);

	DrawTopBar(window);
	DrawButtons(window);

	if (m_isFileMenuOpen)
	{
		m_dropdown.setSize({ DROPDOWN_WIDTH, TOP_BAR_HEIGHT });
		m_dropdown.setPosition(0.f, TOP_BAR_HEIGHT);
		window.draw(m_dropdown);

		DrawText(window, "Open", { TOP_BAR_HEIGHT / 2, TOP_BAR_HEIGHT });
	}
}

MenuView::MenuAction MenuView::HandleClick(const sf::Vector2i mousePos)
{
	if (mousePos.y >= 0 && mousePos.y <= TOP_BAR_HEIGHT && mousePos.x >= 0 && mousePos.x <= DROPDOWN_WIDTH)
	{
		m_isFileMenuOpen = !m_isFileMenuOpen;
		return MenuAction::None;
	}

	if (m_isFileMenuOpen)
	{
		if (mousePos.x >= 0 && mousePos.x <= DROPDOWN_WIDTH && mousePos.y > TOP_BAR_HEIGHT && mousePos.y <= DROPDOWN_WIDTH)
		{
			m_isFileMenuOpen = false;
			return MenuAction::OpenFile;
		}
	}

	m_isFileMenuOpen = false;
	return MenuAction::None;
}

void MenuView::DrawTopBar(sf::RenderWindow& window)
{
	m_topBar.setSize({ static_cast<float>(window.getSize().x), TOP_BAR_HEIGHT });
	window.draw(m_topBar);
}

void MenuView::DrawButtons(sf::RenderWindow& window) const
{
	DrawText(window, "File", { TOP_BAR_HEIGHT / 2, 0.f });
}

void MenuView::DrawText(sf::RenderWindow& window, const std::string& str, const sf::Vector2f textPosition) const
{
	sf::Text text;
	text.setFont(m_font);
	text.setString(str);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);
	text.setPosition(textPosition);
	window.draw(text);
}
