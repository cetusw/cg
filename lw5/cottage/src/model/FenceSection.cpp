#include "model/FenceSection.h"

#include "data/Materials.h"
#include "model/Fence.h"


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
			{ GeometryType::Box, Fence::SectionLength, Fence::PanelThickness, Fence::PanelHeight },
			{ panelPosition, { 0.0f, 0.0f, rotationZ } },
			Materials::Fence,
			{} },
		{ "Fence section post",
			{ GeometryType::Box, Fence::PostSize, Fence::PostSize, Fence::PostHeight },
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
		position.x += Fence::HalfSectionLength;
		break;

	case FenceDirection::PositiveY:
		position.y += Fence::HalfSectionLength;
		break;

	case FenceDirection::NegativeX:
		position.x -= Fence::HalfSectionLength;
		break;

	case FenceDirection::NegativeY:
		position.y -= Fence::HalfSectionLength;
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
