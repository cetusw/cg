#pragma once
#include <glm/vec3.hpp>
#include <string>
#include <vector>

struct Object
{
	std::vector<glm::vec3> vertices;
	std::vector<std::vector<size_t>> faces;
};

class OBJParser
{
public:
	static Object Parse(const std::string& filepath);
};
