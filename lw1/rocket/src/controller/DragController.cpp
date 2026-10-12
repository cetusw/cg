#include "DragController.h"
#include <algorithm>

bool DragController::BeginDrag(
    const sf::Vector2f mousePosition,
    const sf::Vector2f objectPosition,
    const sf::Vector2u windowSize)
{
    m_windowSize = windowSize;
    m_isDragging = true;
    m_startMousePosition = mousePosition;
    m_startObjectPosition = objectPosition;
    return true;
}

sf::Vector2f DragController::DragTo(const sf::Vector2f mousePosition) const
{
    const sf::Vector2f newPosition = m_startObjectPosition + mousePosition - m_startMousePosition;
    float x = std::clamp(newPosition.x, 0.0f, static_cast<float>(m_windowSize.x));
    float y = std::clamp(newPosition.y, 0.0f, static_cast<float>(m_windowSize.y));
    return {x, y};
}

void DragController::EndDrag()
{
    m_isDragging = false;
}

bool DragController::IsDragging() const
{
    return m_isDragging;
}
