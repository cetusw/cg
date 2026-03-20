#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Face {
	std::vector<size_t> vertexIndices;
	glm::u8vec4 color;
	glm::vec3 normal;
};