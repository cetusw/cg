#include "Application.h"
#include "../Utils/PipeDescriptor.h"

Application::Application()
	: m_window(sf::VideoMode(1920, 1080), "Image Viewer")
{
	m_window.setFramerateLimit(60);
}

void Application::Run()
{
	while (m_window.isOpen())
	{
		HandleEvents();

		m_window.clear(sf::Color::White);

		m_backgroundView.Draw(m_window, m_settings);
		m_imageView.Draw(m_window, m_image);
		m_menuView.Draw(m_window);

		m_window.display();
	}
}

void Application::HandleEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		if (event.type == sf::Event::Resized)
		{
			UpdateLayouts();
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			HandleClick(event);
		}
	}
}

void Application::HandleClick(const sf::Event& event)
{
	const sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);
	const auto action = m_menuView.HandleClick(mousePosition);
	if (action == MenuView::MenuAction::OpenFile)
	{
		OpenFileDialog();
	}
}

void Application::UpdateLayouts()
{
	if (m_image.IsLoaded())
	{
		m_imageView.UpdateLayout(m_window.getSize(), m_image.GetSize());
	}
}

void Application::OpenFileDialog()
{
	std::string result;

	const PipeDescriptor pipe("zenity --file-selection --title=\"Open Image\" --file-filter=\"*.png *.jpg *.jpeg *.bmp\"", "r");

	if (pipe.IsOpen())
	{
		char buffer[1024];

		while (fgets(buffer, sizeof(buffer), pipe.Get()))
		{
			result += buffer;
		}

		if (!result.empty() && result.back() == '\n')
		{
			result.pop_back();
		}
	}

	if (!result.empty())
	{
		if (m_image.LoadImage(result))
		{
			UpdateLayouts();
		}
	}
}