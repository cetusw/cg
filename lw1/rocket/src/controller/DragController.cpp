#include "DragController.h"

bool DragController::BeginDrag(
    const sf::Vector2f mousePosition,
    const sf::Vector2f objectPosition)
{
    m_isDragging = true;
    m_startMousePosition = mousePosition;
    m_startObjectPosition = objectPosition;
    return true;
}

sf::Vector2f DragController::DragTo(const sf::Vector2f mousePosition) const
{
    return m_startObjectPosition + mousePosition - m_startMousePosition;
}

void DragController::EndDrag()
{
    m_isDragging = false;
}

bool DragController::IsDragging() const
{
    return m_isDragging;
}
