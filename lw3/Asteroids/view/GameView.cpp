#include "GameView.h"
#include <GL/glut.h>

void GameView::DrawShip(const Ship& ship)
{
	glPushMatrix();

	glTranslatef(ship.GetX(), ship.GetY(), 0);
	glRotatef(ship.GetAngle(), 0, 0, 1);

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINE_LOOP);
	glVertex2f(0.08f, 0.0f);
	glVertex2f(-0.07f, 0.06f);
	glVertex2f(-0.04f, 0.0f);
	glVertex2f(-0.07f, -0.06f);
	glEnd();

	glPopMatrix();
}

void GameView::Reshape(const int width, const int height)
{
	const float aspect = static_cast<float>(width) / static_cast<float>(height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width >= height)
	{
		glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -1.0, 1.0);
	}
	else
	{
		glOrtho(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect, -1.0, 1.0);
	}

	glMatrixMode(GL_MODELVIEW);
}