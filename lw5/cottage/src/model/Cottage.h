#pragma once

#include "model/Fence.h"
#include "model/Garage.h"
#include "model/House.h"
#include "model/Porch.h"
#include "types/SceneObject.h"

#include <glm/vec3.hpp>
#include <vector>

class Cottage
{
public:
	explicit Cottage(glm::vec3 position);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;

private:
	glm::vec3 m_position;
	House m_house;
	Garage m_garage;
	Porch m_porch;
	Fence m_fence;
};
