#include "AppController.h"

AppController::AppController(
	Image& image,
	ImageController& imageController,
	WindowSettings& windowSettings,
	Menu& menu,
	sf::RenderWindow& window)
	: m_window(window)
	, m_image(image)
	, m_windowSettings(windowSettings)
	, m_menu(menu)
	, m_imageController(imageController)
{
}

void AppController::DispatchEvent(const sf::Event& event) const
{
	if (event.type == sf::Event::Closed)
	{
		m_window.close();
	}

	if (event.type == sf::Event::Resized)
	{
		m_windowSettings.SetWindowSize(m_window.getSize());
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		HandleMouseClick(event.mouseButton);
	}
}

void AppController::HandleMouseClick(const sf::Event::MouseButtonEvent& mouse) const
{
	const sf::Vector2i mousePosition(mouse.x, mouse.y);
	const auto action = m_menu.GetItemAt(mousePosition);

	if (action == Menu::Item::File)
	{
		m_menu.ToggleFileMenu();
	}
	else if (action == Menu::Item::OpenFile)
	{
		m_imageController.OnOpenFile();
		m_menu.Close();
	}
	else
	{
		m_menu.Close();
	}
}