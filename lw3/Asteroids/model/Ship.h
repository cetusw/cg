#pragma once

class Ship
{
public:
	void Rotate(float speed, float deltaTime);
	void Thrust(float acceleration, float deltaTime);
	void Update(float deltaTime, float worldWidth, float worldHeight);

	[[nodiscard]] float GetX() const;
	[[nodiscard]] float GetY() const;
	[[nodiscard]] float GetDX() const;
	[[nodiscard]] float GetDY() const;
	[[nodiscard]] float GetAngle() const;

private:
	float m_x = 0.f;
	float m_y = 0.f;
	float m_dx = 0.f;
	float m_dy = 0.f;
	float m_angle = 90.f;

	void ScreenWrap(float width, float height);
};