#pragma once

#include "model/FenceSection.h"

#include <glm/vec3.hpp>
#include <vector>

class Lamp
{
public:
	explicit Lamp(glm::vec3 position);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;

private:
	glm::vec3 m_position;
};
