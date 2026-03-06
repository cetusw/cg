#include "AsteroidsApplication.h"
#include "view/GameView.h"
#include <GL/glut.h>

AsteroidsApplication::AsteroidsApplication(
	const char* title, const int width, const int height)
	: GLApplication(title, width, height)
{
}

void AsteroidsApplication::OnInit()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void AsteroidsApplication::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	GameView::DrawShip(m_ship);
}

void AsteroidsApplication::OnReshape(const int width, const int height)
{
	GameView::Reshape(width, height);
	const float aspect = static_cast<float>(width) / static_cast<float>(height);
	if (width >= height)
	{
		m_worldWidth = aspect;
		m_worldHeight = 1.0f;
	}
	else
	{
		m_worldWidth = 1.0f;
		m_worldHeight = 1.0f / aspect;
	}
}

void AsteroidsApplication::OnIdle()
{
	const float dt = GetDeltaTime();

	constexpr float rotationSpeed = 250.0f;
	constexpr float thrustPower = 1.5f;

	if (IsKeyPressed('a') || IsKeyPressed('A') || IsSpecialKeyPressed(GLUT_KEY_LEFT))
	{
		m_ship.Rotate(rotationSpeed, dt);
	}
	if (IsKeyPressed('d') || IsKeyPressed('D') || IsSpecialKeyPressed(GLUT_KEY_RIGHT))
	{
		m_ship.Rotate(-rotationSpeed, dt);
	}

	if (IsKeyPressed('w') || IsKeyPressed('W') || IsSpecialKeyPressed(GLUT_KEY_UP))
	{
		m_ship.Thrust(thrustPower, dt);
	}

	m_ship.Update(dt, m_worldWidth, m_worldHeight);
	PostRedisplay();
}
