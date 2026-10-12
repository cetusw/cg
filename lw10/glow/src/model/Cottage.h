#pragma once

#include "model/Fence.h"
#include "model/Garage.h"
#include "model/House.h"
#include "model/Lamp.h"
#include "model/Porch.h"
#include "types/SceneObject.h"

#include <cstddef>
#include <glm/vec3.hpp>
#include <vector>

class Cottage
{
public:
	explicit Cottage(glm::vec3 position);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;
	[[nodiscard]] std::size_t GetSpotLightCount() const;
	[[nodiscard]] const SpotLight& GetSpotLight(std::size_t index) const;

private:
	static constexpr glm::vec3 GarageOffset{ 5.0f, 0.0f, 0.0f };
	static constexpr glm::vec3 PorchOffset{ 1.5f, 3.0f, 0.0f };
	static constexpr glm::vec3 Lamp1PositionOffset{ 6.0f, 3.5f, 0.0f };
	static constexpr glm::vec3 Lamp1TargetOffset{ 5.0f, 3.5f, 0.0f };
	static constexpr glm::vec3 Lamp2PositionOffset{ 0.5f, 5.0f, 0.0f };
	static constexpr glm::vec3 Lamp2TargetOffset{ 1.5f, 5.0f, 0.0f };

	glm::vec3 m_position;
	House m_house;
	Garage m_garage;
	Porch m_porch;
	Fence m_fence;
	std::vector<Lamp> m_lamps;
};
