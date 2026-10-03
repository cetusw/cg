#include "model/FenceSection.h"

#include "consts/CottageDimensions.h"
#include "data/Materials.h"

using namespace FenceDimensions;

FenceSection::FenceSection(
	const glm::vec3 position,
	const FenceDirection direction)
	: m_position(position)
	, m_direction(direction)
{
}

std::vector<SceneObject> FenceSection::CreateObjects() const
{
	const glm::vec3 panelPosition = GetPanelPosition();
	const float rotationZ = GetRotationZ();

	return {
		{ "Fence panel",
			{ GeometryType::Box, SectionLength, PanelThickness, PanelHeight },
			{ panelPosition, { 0.0f, 0.0f, rotationZ } },
			Materials::Fence,
			{} },
		{ "Fence section post",
			{ GeometryType::Box, PostSize, PostSize, PostHeight },
			{ m_position },
			Materials::Fence,
			{} }
	};
}

glm::vec3 FenceSection::GetPanelPosition() const
{
	glm::vec3 position = m_position;

	switch (m_direction)
	{
	case FenceDirection::PositiveX:
		position.x += SectionLength / 2.0f;
		break;

	case FenceDirection::PositiveY:
		position.y += SectionLength / 2.0f;
		break;

	case FenceDirection::NegativeX:
		position.x -= SectionLength / 2.0f;
		break;

	case FenceDirection::NegativeY:
		position.y -= SectionLength / 2.0f;
		break;
	}

	return position;
}

float FenceSection::GetRotationZ() const
{
	switch (m_direction)
	{
	case FenceDirection::PositiveX:
		return 0.0f;
	case FenceDirection::PositiveY:
		return 90.0f;
	case FenceDirection::NegativeX:
		return 180.0f;
	case FenceDirection::NegativeY:
		return 270.0f;
	}

	return 0.0f;
}
