#pragma once

#include "Material.h"

#include <glm/vec3.hpp>

struct PointLight
{
	glm::vec3 position;
	RgbColor ambient;
	RgbColor diffuse;
	RgbColor specular;
};
