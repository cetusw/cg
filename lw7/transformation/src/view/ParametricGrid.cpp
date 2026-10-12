#include "view/ParametricGrid.h"

#include <GL/glew.h>

void ParametricGrid::Draw()
{
	constexpr int GridSegments = 80;

	for (int i = 0; i < GridSegments; ++i)
	{
		constexpr float MaxCoordinate = 1.5f;
		constexpr float MinCoordinate = -1.5f;
		const float x0 = MinCoordinate + (MaxCoordinate - MinCoordinate) * i / GridSegments;
		const float x1 = MinCoordinate + (MaxCoordinate - MinCoordinate) * (i + 1) / GridSegments;

		for (int j = 0; j < GridSegments; ++j)
		{
			const float y0 = MinCoordinate + (MaxCoordinate - MinCoordinate) * j / GridSegments;
			const float y1 = MinCoordinate + (MaxCoordinate - MinCoordinate) * (j + 1) / GridSegments;

			glBegin(GL_QUADS);
			glVertex3f(x0, y0, 0.0f);
			glVertex3f(x1, y0, 0.0f);
			glVertex3f(x1, y1, 0.0f);
			glVertex3f(x0, y1, 0.0f);
			glEnd();
		}
	}
}
