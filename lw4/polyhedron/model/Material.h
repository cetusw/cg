#pragma once

#include "Light.h"

struct MaterialDescription
{
	RgbColor ambient;
	RgbColor diffuse;
	RgbColor specular;
	float shininess{};
};
