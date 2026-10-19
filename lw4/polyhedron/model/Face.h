#pragma once

#include <glm/glm.hpp>

#include <vector>

struct Face
{
	std::vector<size_t> vertexIndices;
	glm::vec3 color;
	glm::vec3 normal;
};
