#include "LetterView.h"
#include <SFML/Graphics/ConvexShape.hpp>

void LetterView::Render(sf::RenderWindow& window, const Letter& letter)
{
	for (const auto& part : letter.GetLetterParts())
	{
		sf::ConvexShape polygon;
		polygon.setPointCount(part.points.size());

		for (size_t i = 0; i < part.points.size(); ++i)
		{
			sf::Vector2f globalPosition = CalculateGlobalPosition(
				letter.GetPosition(), part.points[i]);
			polygon.setPoint(i, globalPosition);
		}

		polygon.setFillColor(part.color);
		window.draw(polygon);
	}
}

sf::Vector2f LetterView::CalculateGlobalPosition(
	const sf::Vector2f letterPosition,
	const sf::Vector2f partPosition)
{
	return {
		letterPosition.x + partPosition.x,
		letterPosition.y + partPosition.y
	};
}