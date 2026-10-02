#include "model/Fence.h"

#include "consts/CottageDimensions.h"
#include "data/Materials.h"

#include <array>

Fence::Fence(const glm::vec3 position)
	: m_position(position)
{
}

std::vector<SceneObject> Fence::CreateObjects() const
{
	using namespace FenceDimensions;

	std::vector<SceneObject> objects;
	objects.reserve(25);

	constexpr std::array backPostOffsets{
		-HalfWidth,
		-HalfWidth / 2.0f,
		0.0f,
		HalfWidth / 2.0f,
		HalfWidth
	};
	for (const float xOffset : backPostOffsets)
	{
		objects.push_back({
			"Fence back post",
			{ GeometryType::Box, PostSize, PostSize, Height },
			{ { m_position.x + xOffset, m_position.y - HalfDepth, m_position.z } },
			Materials::Fence,
			{}
		});
	}

	constexpr std::array frontPostOffsets{
		-HalfWidth,
		GateLeftX,
		GateRightX,
		HalfWidth
	};
	for (const float xOffset : frontPostOffsets)
	{
		objects.push_back({
			"Fence front post",
			{ GeometryType::Box, PostSize, PostSize, Height },
			{ { m_position.x + xOffset, m_position.y + HalfDepth, m_position.z } },
			Materials::Fence,
			{}
		});
	}

	constexpr std::array sidePostOffsets{
		-HalfDepth / 3.0f,
		HalfDepth / 3.0f
	};
	for (const float yOffset : sidePostOffsets)
	{
		objects.push_back({
			"Fence left post",
			{ GeometryType::Box, PostSize, PostSize, Height },
			{ { m_position.x - HalfWidth, m_position.y + yOffset, m_position.z } },
			Materials::Fence,
			{}
		});
		objects.push_back({
			"Fence right post",
			{ GeometryType::Box, PostSize, PostSize, Height },
			{ { m_position.x + HalfWidth, m_position.y + yOffset, m_position.z } },
			Materials::Fence,
			{}
		});
	}

	constexpr std::array railHeights{
		LowerRailHeight,
		UpperRailHeight
	};
	for (const float railHeight : railHeights)
	{
		objects.push_back({
			"Fence back rail",
			{ GeometryType::Box, 2.0f * HalfWidth, RailThickness, RailThickness },
			{ { m_position.x, m_position.y - HalfDepth, m_position.z + railHeight } },
			Materials::Fence,
			{}
		});
		objects.push_back({
			"Fence left rail",
			{ GeometryType::Box, RailThickness, 2.0f * HalfDepth, RailThickness },
			{ { m_position.x - HalfWidth, m_position.y, m_position.z + railHeight } },
			Materials::Fence,
			{}
		});
		objects.push_back({
			"Fence right rail",
			{ GeometryType::Box, RailThickness, 2.0f * HalfDepth, RailThickness },
			{ { m_position.x + HalfWidth, m_position.y, m_position.z + railHeight } },
			Materials::Fence,
			{}
		});
		objects.push_back({
			"Fence front left rail",
			{ GeometryType::Box, FrontLeftRailWidth, RailThickness, RailThickness },
			{ { m_position.x + FrontLeftRailCenterX, m_position.y + HalfDepth, m_position.z + railHeight } },
			Materials::Fence,
			{}
		});
		objects.push_back({
			"Fence front right rail",
			{ GeometryType::Box, FrontRightRailWidth, RailThickness, RailThickness },
			{ { m_position.x + FrontRightRailCenterX, m_position.y + HalfDepth, m_position.z + railHeight } },
			Materials::Fence,
			{}
		});
	}

	return objects;
}
