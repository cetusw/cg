#pragma once

#include "Geometry.h"
#include "Material.h"
#include "Transform.h"

#include <string>
#include <optional>

struct SceneObject
{
	std::string name;
	GeometryDescription geometry;
	Transform transform;
	MaterialDescription material;
	std::string texturePath;
	std::optional<RgbColor> glowColor = std::nullopt;
};
