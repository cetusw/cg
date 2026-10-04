#pragma once

#include <glm/vec3.hpp>

struct LinearMovement
{
	glm::vec3 start;
	glm::vec3 end;
	float speed{};
	bool isMovingToEnd = true; // TODO для чего?
};
