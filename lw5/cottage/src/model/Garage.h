#pragma once

#include "types/SceneObject.h"

#include <glm/vec3.hpp>
#include <vector>

class Garage
{
public:
	explicit Garage(glm::vec3 position);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;

private:
	glm::vec3 m_position;
};
