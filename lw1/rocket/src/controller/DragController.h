#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class DragController
{
public:
    bool BeginDrag(
        sf::Vector2f mousePosition,
        sf::Vector2f objectPosition);

    [[nodiscard]] sf::Vector2f DragTo(sf::Vector2f mousePosition) const;

    void EndDrag();

    [[nodiscard]] bool IsDragging() const;

private:
    bool m_isDragging = false;
    sf::Vector2f m_startMousePosition;
    sf::Vector2f m_startObjectPosition;
};
