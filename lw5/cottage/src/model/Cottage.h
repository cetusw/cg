#pragma once

#include "model/Scene.h"

#include "model/Garage.h"
#include "model/Fence.h"
#include "model/House.h"
#include "model/Porch.h"

#include <vector>

class Cottage
{
public:
	explicit Cottage(Vector3 position);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;

private:
	Vector3 m_position;
	House m_house;
	Garage m_garage;
	Porch m_porch;
	Fence m_fence;
};
