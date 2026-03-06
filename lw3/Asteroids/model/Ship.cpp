#include "Ship.h"
#include <cmath>

void Ship::Rotate(const float speed, const float deltaTime)
{
	m_angle += speed * deltaTime;
}

void Ship::Thrust(const float acceleration, const float deltaTime)
{
	const float rad = m_angle * static_cast<float>(M_PI / 180.f);
	m_dx += cosf(rad) * acceleration * deltaTime;
	m_dy += sinf(rad) * acceleration * deltaTime;
}

void Ship::Update(const float deltaTime, const float worldWidth, const float worldHeight)
{
	m_x += m_dx * deltaTime;
	m_y += m_dy * deltaTime;

	constexpr float friction = 0.5f;
	m_dx -= m_dx * friction * deltaTime;
	m_dy -= m_dy * friction * deltaTime;

	ScreenWrap(worldWidth, worldHeight);
}

float Ship::GetX() const
{
	return m_x;
}

float Ship::GetY() const
{
	return m_y;
}

float Ship::GetDX() const
{
	return m_dx;
}

float Ship::GetDY() const
{
	return m_dy;
}

float Ship::GetAngle() const
{
	return m_angle;
}

void Ship::ScreenWrap(const float width, const float height)
{
	constexpr float margin = 0.1f;

	if (m_x > width + margin)
	{
		m_x = -width - margin;
	}
	else if (m_x < -width - margin)
	{
		m_x = width + margin;
	}

	if (m_y > height + margin)
	{
		m_y = -height - margin;
	}
	else if (m_y < -height - margin)
	{
		m_y = height + margin;
	}
}