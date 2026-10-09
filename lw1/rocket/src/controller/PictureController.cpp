#include "PictureController.h"

#include <SFML/Window/Mouse.hpp>

PictureController::PictureController(Picture &picture)
    : m_picture(picture)
{
}

void PictureController::HandleEvent(const sf::Event &event, const sf::RenderWindow &window)
{
    HandleMouseButtonPressed(event, window);
    HandleMouseMoved(event, window);
    HandleMouseReleased(event);
    HandleFocusLost(event);
}

void PictureController::HandleMouseButtonPressed(const sf::Event &event, const sf::RenderWindow &window)
{
    if (const auto *mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mousePressed->button != sf::Mouse::Button::Left)
        {
            return;
        }

        const sf::Vector2f mousePosition = GetMousePosition(mousePressed->position, window);

        if (!m_picture.Contains(mousePosition))
        {
            return;
        }

        m_dragController.BeginDrag(mousePosition, m_picture.GetPosition());
    }
}

void PictureController::HandleMouseMoved(const sf::Event &event, const sf::RenderWindow &window) const
{
    if (const auto *mouseMoved = event.getIf<sf::Event::MouseMoved>())
    {
        if (!m_dragController.IsDragging())
        {
            return;
        }
        const sf::Vector2f mousePosition = GetMousePosition(mouseMoved->position, window);
        const sf::Vector2f positionAfterDrag = m_dragController.DragTo(mousePosition);
        m_picture.SetPosition(positionAfterDrag);
    }
}

void PictureController::HandleMouseReleased(const sf::Event &event)
{
    if (const auto *mouseReleased = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouseReleased->button != sf::Mouse::Button::Left)
        {
            return;
        }
        m_dragController.EndDrag();
    }
}

void PictureController::HandleFocusLost(const sf::Event &event)
{
    if (event.is<sf::Event::FocusLost>())
    {
        m_dragController.EndDrag();
    }
}

sf::Vector2f PictureController::GetMousePosition(
    const sf::Vector2i &pixelPosition,
    const sf::RenderWindow &window)
{
    return window.mapPixelToCoords(pixelPosition);
}
