#pragma once

#include "model/Scene.h"

#include <vector>

class Fence
{
public:
	explicit Fence(Vector3 position);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;

private:
	Vector3 m_position;
};
