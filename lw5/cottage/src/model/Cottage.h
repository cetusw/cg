#pragma once

#include "Lamp.h"
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
	static constexpr glm::vec3 GarageOffset{ 5.0f, 0.0f, 0.0f };
	static constexpr glm::vec3 PorchOffset{ 1.5f, 3.0f, 0.0f };
	static constexpr glm::vec3 LampOffset{ 0.0f, 5.0f, 0.0f };


	glm::vec3 m_position;
	House m_house;
	Garage m_garage;
	Porch m_porch;
	Fence m_fence;
	Lamp m_lamp;
};
