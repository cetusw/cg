#pragma once

#include <variant>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using Primitive = std::variant<sf::RectangleShape, sf::CircleShape, sf::ConvexShape>;
