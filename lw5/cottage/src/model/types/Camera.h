#pragma once

#include <glm/vec3.hpp>

struct Camera
{
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
};
