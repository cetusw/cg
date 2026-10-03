#pragma once

#include "types/SceneObject.h"

#include <glm/vec3.hpp>
#include <vector>

enum class FenceDirection
{
	PositiveX,
	PositiveY,
	NegativeX,
	NegativeY
};

class FenceSection
{
public:
	FenceSection(glm::vec3 position, FenceDirection direction);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;

private:
	[[nodiscard]] glm::vec3 GetPanelPosition() const;
	[[nodiscard]] float GetRotationZ() const;

	glm::vec3 m_position;
	FenceDirection m_direction;
};