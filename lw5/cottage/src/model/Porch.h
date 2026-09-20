#pragma once

#include "model/Scene.h"

#include <vector>

class Porch
{
public:
	explicit Porch(Vector3 position);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;

private:
	Vector3 m_position;
};
