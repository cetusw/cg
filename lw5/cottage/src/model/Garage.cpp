#include "model/Garage.h"

#include "consts/CottageDimensions.h"
#include "data/Materials.h"

Garage::Garage(const glm::vec3 position)
	: m_position(position)
{
}

std::vector<SceneObject> Garage::CreateObjects() const
{
	using namespace GarageDimensions;

	return {
		{ "Garage body",
			{ GeometryType::Box, BodyWidth, BodyDepth, BodyHeight },
			{ m_position },
			Materials::Wall,
			"assets/brick.jpg" },
		{ "Garage door",
			{ GeometryType::Box, DoorWidth, DoorThickness, DoorHeight },
			{ { m_position.x, m_position.y + BodyDepth / 2.0f + DoorThickness / 2.0f, m_position.z } },
			Materials::Door,
			{} },
		{ "Garage window",
			{ GeometryType::Box, WindowThickness, WindowWidth, WindowHeight },
			{ { m_position.x + BodyWidth / 2.0f + WindowThickness / 2.0f, m_position.y, m_position.z + WindowBaseHeight } },
			Materials::Window,
			{} }
	};
}
