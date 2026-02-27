#include "Application.h"

Application::Application()
	: m_window(sf::VideoMode(1920, 1080), "Image Viewer")
	, m_imageController(m_image)
	, m_appController(m_image, m_imageController, m_windowSettings, m_menu, m_window)
{
	m_window.setFramerateLimit(60);
	m_windowSettings.Add(&m_imageView);
	m_windowSettings.Add(&m_menuView);
	m_menu.Add(&m_menuView);
}

void Application::Run()
{
	while (m_window.isOpen())
	{
		sf::Event event{};
		while (m_window.pollEvent(event))
		{
			m_appController.DispatchEvent(event);
		}

		m_window.clear();
		m_backgroundView.Draw(m_window);
		m_imageView.Draw(m_window, m_image);
		m_menuView.Draw(m_window, m_menu);
		m_window.display();
	}
}
