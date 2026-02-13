#include "Letter.h"

void Letter::Update(const float deltaTime)
{
	if (m_timer < m_jumpDelay)
	{
		m_timer += deltaTime;
		return;
	}

	m_velocityY += m_acceleration * deltaTime;
	m_position.y += m_velocityY * deltaTime;

	HandleCollision();
}

sf::Vector2f Letter::GetPosition() const
{
	return m_position;
}

std::vector<LetterPart> Letter::GetLetterParts() const
{
	return m_letterParts;
}

void Letter::HandleCollision()
{
	if (m_position.y >= m_floor)
	{
		m_position.y = m_floor;
		m_velocityY = m_jumpForce;
	}
}
