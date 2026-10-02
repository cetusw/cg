#pragma once

#include "Geometry.h"
#include "Material.h"
#include "Transform.h"

#include <string>

struct SceneObject
{
	std::string name;
	GeometryDescription geometry;
	Transform transform;
	MaterialDescription material;
	std::string texturePath;
};
