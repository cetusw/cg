#include "model/Porch.h"

#include "data/Materials.h"

Porch::Porch(const glm::vec3 position)
	: m_position(position)
{
}

std::vector<SceneObject> Porch::CreateObjects() const
{
	return {
		{ "Porch",
			{ GeometryType::Box, PlatformWidth, PlatformDepth, PlatformHeight },
			{ m_position },
			Materials::Concrete,
			"assets/concrete.jpg" },
		{ "Column",
			{ GeometryType::Box, ColumnWidth, ColumnWidth, ColumnHeight },
			{ { m_position.x + ColumnOffset.x, m_position.y + ColumnOffset.y, m_position.z + ColumnOffset.z } },
			Materials::Concrete,
			"assets/concrete.jpg" }
	};
}
