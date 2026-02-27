#include "WindowSettings.h"

void WindowSettings::SetWindowSize(const sf::Vector2u size)
{
	m_windowSize = size;
	Notify();
}

sf::Vector2u WindowSettings::GetWindowSize() const
{
	return m_windowSize;
}