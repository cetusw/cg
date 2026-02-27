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

	m_text.setFont(m_font);
	m_text.setCharacterSize(50);
	m_text.setFillColor(sf::Color::White);
}

void MenuView::Draw(sf::RenderWindow& window, const Menu& menu)
{
	const sf::View uiView(sf::FloatRect(0.f, 0.f,
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)));
	window.setView(uiView);

	if (m_needsUpdate)
	{
		UpdateLayout(window, menu);
		m_needsUpdate = false;
	}

	window.draw(m_topBar);
	DrawText(window, "File", { Menu::TOP_BAR_HEIGHT / 2, 0.f });

	if (menu.IsFileMenuOpen())
	{
		window.draw(m_dropdown);
		DrawText(window, "Open", { Menu::TOP_BAR_HEIGHT / 2, Menu::TOP_BAR_HEIGHT });
	}
}

void MenuView::OnModelChanged()
{
	m_needsUpdate = true;
}

void MenuView::DrawText(sf::RenderWindow& window, const std::string& str, const sf::Vector2f textPosition)
{
	m_text.setString(str);
	m_text.setPosition(textPosition);
	window.draw(m_text);
}

void MenuView::UpdateLayout(const sf::RenderWindow& window, const Menu& menu)
{
	m_topBar.setSize({ static_cast<float>(window.getSize().x), Menu::TOP_BAR_HEIGHT });
	if (menu.IsFileMenuOpen())
	{
		m_dropdown.setSize({ Menu::DROPDOWN_WIDTH, Menu::TOP_BAR_HEIGHT });
		m_dropdown.setPosition(0.f, Menu::TOP_BAR_HEIGHT);
	}
}
