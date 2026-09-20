#pragma once

#include "model/Scene.h"

#include <vector>

class Cottage
{
public:
	explicit Cottage(Vector3 position);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;

private:
	Vector3 m_position;
};
