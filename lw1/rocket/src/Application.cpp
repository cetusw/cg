#include "Application.h"

#include <optional>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/VideoMode.hpp>

Application::Application()
    : m_window(sf::VideoMode({900, 700}), "Rocket")
      , m_pictureController(m_rocket.GetPicture())
{
    m_window.setFramerateLimit(60);
}

void Application::Run()
{
    while (m_window.isOpen())
    {
        ProcessEvents();
        Render();
    }
}

void Application::ProcessEvents()
{
    while (const std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
            continue;
        }

        if (const auto *resized = event->getIf<sf::Event::Resized>())
        {
            m_window.setView(sf::View(sf::FloatRect({0.0f, 0.0f}, sf::Vector2f(resized->size))));
        }

        m_pictureController.HandleEvent(*event, m_window);
    }
}

void Application::Render()
{
    m_window.clear(sf::Color::White);
    PictureView::Render(m_window, m_rocket.GetPicture());
    m_window.display();
}
