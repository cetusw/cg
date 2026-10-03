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
	static constexpr float BodyWidth = 4.0f;
	static constexpr float HalfBodyWidth = BodyWidth / 2.0f;
	static constexpr float BodyDepth = 4.0f;
	static constexpr float HalfBodyDepth = BodyDepth / 2.0f;
	static constexpr float BodyHeight = 2.0f;

	static constexpr float DoorWidth = 2.0f;
	static constexpr float DoorHeight = 2.0f;
	static constexpr float DoorThickness = 0.05f;
	static constexpr float HalfDoorThickness = DoorThickness / 2.0f;

	static constexpr float WindowThickness = 0.05f;
	static constexpr float HalfWindowThickness = WindowThickness / 2.0f;
	static constexpr float WindowWidth = 2.0f;
	static constexpr float WindowHeight = 1.0f;
	static constexpr float WindowBaseHeight = 0.75f;

	glm::vec3 m_position;
};
