#include "Menu.h"

Menu::Item Menu::GetItemAt(const sf::Vector2i mousePosition) const
{
	if (mousePosition.y >= 0
		&& mousePosition.y <= static_cast<int>(TOP_BAR_HEIGHT)
		&& mousePosition.x >= 0
		&& mousePosition.x <= static_cast<int>(DROPDOWN_WIDTH))
	{
		return Item::File;
	}
	if (mousePosition.y > static_cast<int>(TOP_BAR_HEIGHT)
		&& mousePosition.y <= static_cast<int>(TOP_BAR_HEIGHT) * 2
		&& mousePosition.x >= 0
		&& mousePosition.x <= static_cast<int>(DROPDOWN_WIDTH)
		&& m_isFileMenuOpen)
	{
		return Item::OpenFile;
	}
	return Item::None;
}

void Menu::ToggleFileMenu()
{
	m_isFileMenuOpen = !m_isFileMenuOpen;
	Notify();
}

void Menu::Close()
{
	if (m_isFileMenuOpen)
	{
		m_isFileMenuOpen = false;
		Notify();
	}
}

bool Menu::IsFileMenuOpen() const
{
	return m_isFileMenuOpen;
}