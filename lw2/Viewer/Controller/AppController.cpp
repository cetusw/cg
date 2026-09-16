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

void AppController::DispatchEvent(const sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		m_window.close();
	}
	else if (event.type == sf::Event::Resized)
	{
		m_windowSettings.SetWindowSize(m_window.getSize());
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		HandleMouseClick(event.mouseButton);
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		HandleMouseRelease(event.mouseButton);
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		HandleMouseMove(event.mouseMove);
	}
}

void AppController::HandleMouseClick(const sf::Event::MouseButtonEvent& mouse)
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
		const sf::Vector2u windowSize = m_windowSettings.GetWindowSize();

		const sf::Vector2f worldPos = m_image.TransformPixelToWorld(mousePosition, windowSize);

		if (m_image.Contains(worldPos))
		{
			m_isDragging = true;
			m_lastMousePos = mousePosition;
		}
	}
}

void AppController::HandleMouseRelease(const sf::Event::MouseButtonEvent& mouse)
{
	if (mouse.button == sf::Mouse::Left)
	{
		m_isDragging = false;
	}
}

void AppController::HandleMouseMove(const sf::Event::MouseMoveEvent& mouse)
{
	if (m_isDragging)
	{
		const sf::Vector2i currentMousePos(mouse.x, mouse.y);
		const auto delta = static_cast<sf::Vector2f>(m_lastMousePos - currentMousePos);

		m_image.SetViewCenter(m_image.GetViewCenter() + delta);

		m_lastMousePos = currentMousePos;
	}
}