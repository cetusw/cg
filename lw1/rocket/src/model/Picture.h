#pragma once

#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "Primitive.h"

class Picture
{
public:
	explicit Picture(sf::Vector2f position);

	void AddPrimitive(Primitive primitive);

	[[nodiscard]] bool Contains(sf::Vector2f point) const;

	[[nodiscard]] const std::vector<Primitive>& GetPrimitives() const;
	[[nodiscard]] const sf::Vector2f& GetPosition() const;
	void SetPosition(sf::Vector2f position);

private:
	std::vector<Primitive> m_primitives;
	sf::Vector2f m_position;
};
