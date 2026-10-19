#pragma once

#include <glm/vec3.hpp>

struct RgbColor
{
	float red{};
	float green{};
	float blue{};
};

struct PointLight
{
	glm::vec3 position;
	RgbColor ambient;
	RgbColor diffuse;
	RgbColor specular;
};
