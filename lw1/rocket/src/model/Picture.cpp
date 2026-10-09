#include "Picture.h"

#include <algorithm>
#include <utility>

Picture::Picture(const sf::Vector2f position)
    : m_position(position)
{
}

void Picture::AddPrimitive(Primitive primitive)
{
    m_primitives.push_back(std::move(primitive));
}

bool Picture::Contains(const sf::Vector2f point) const
{
    const sf::Vector2f localPoint = point - m_position;

    for (const Primitive &primitive: m_primitives)
    {
        const bool contains = std::visit(
            [localPoint](const auto &shape)
            {
                return shape.getGlobalBounds().contains(localPoint);
            },
            primitive);

        if (contains)
        {
            return true;
        }
    }

    return false;
}

const std::vector<Primitive> &Picture::GetPrimitives() const
{
    return m_primitives;
}

const sf::Vector2f &Picture::GetPosition() const
{
    return m_position;
}

void Picture::SetPosition(const sf::Vector2f position)
{
    m_position = position;
}
