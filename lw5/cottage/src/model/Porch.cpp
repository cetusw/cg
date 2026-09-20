#include "model/Porch.h"

#include "model/CottageDimensions.h"
#include "model/Materials.h"

Porch::Porch(const Vector3 position)
	: m_position(position)
{
}

std::vector<SceneObject> Porch::CreateObjects() const
{
	using namespace PorchDimensions;

	return {
		{ "Porch",
			{ GeometryType::Box, PlatformWidth, PlatformDepth, PlatformHeight },
			{ m_position },
			Materials::Wall,
			"assets/concrete.jpg" },
		{ "Column",
			{ GeometryType::Box, ColumnWidth, ColumnWidth, ColumnHeight },
			{ { m_position.x + ColumnOffset.x, m_position.y + ColumnOffset.y, m_position.z + ColumnOffset.z } },
			Materials::Wall,
			"assets/concrete.jpg" }
	};
}
