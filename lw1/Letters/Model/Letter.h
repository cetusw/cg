#ifndef LETTERS_LETTER_H
#define LETTERS_LETTER_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

struct LetterPart
{
	std::vector<sf::Vector2f> points;
	sf::Color color{};
};

class Letter
{
public:
	Letter(
		const float startX,
		const float startY,
		const float delay,
		const std::vector<LetterPart>& shapes)
		: m_position({ startX, startY })
		, m_floor(startY)
		, m_letterParts(shapes)
		, m_jumpDelay(delay)
	{
	}

	void Update(float deltaTime);

	sf::Vector2f GetPosition() const;
	std::vector<LetterPart> GetLetterParts() const;

private:
	sf::Vector2f m_position;
	float m_floor;
	float m_velocityY = 0;
	const float m_acceleration = 980.0f;
	const float m_jumpForce = -500.0f;
	std::vector<LetterPart> m_letterParts{};
	float m_jumpDelay;
	float m_timer = 0;

	void HandleCollision();
};

#endif // LETTERS_LETTER_H
