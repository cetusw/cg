#include "view/ParametricCurve.h"

#include <GL/glew.h>

#include <numbers>

void ParametricCurve::Draw()
{
	constexpr int SegmentCount = 2000;
	constexpr float MaximumX = 2.0f * std::numbers::pi_v<float>;

	glBegin(GL_LINE_STRIP);
	for (int segmentIndex = 0; segmentIndex <= SegmentCount; ++segmentIndex)
	{
		const float x = MaximumX * static_cast<float>(segmentIndex) / SegmentCount;
		glVertex3f(x, 0.0f, 0.0f);
	}
	glEnd();
}
