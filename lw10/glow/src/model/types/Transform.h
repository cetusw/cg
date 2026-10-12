#pragma once

#include <glm/vec3.hpp>

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation{
		0.0f,
		0.0f,
		0.0f
	};
	glm::vec3 scale{
		1.0f,
		1.0f,
		1.0f
	};
};
