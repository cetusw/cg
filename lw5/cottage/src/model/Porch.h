#pragma once

#include "types/SceneObject.h"

#include <glm/vec3.hpp>
#include <vector>

class Porch
{
public:
	explicit Porch(glm::vec3 position);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;

private:
	static constexpr float PlatformWidth = 3.0f;
	static constexpr float PlatformDepth = 2.0f;
	static constexpr float PlatformHeight = 0.5f;

	static constexpr float ColumnWidth = 0.2f;
	static constexpr float ColumnHeight = 2.0f;
	static constexpr glm::vec3 ColumnOffset{ 1.0f, 0.5f, 0.0f };

	glm::vec3 m_position;
};
