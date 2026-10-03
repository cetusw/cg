#include "model/Garage.h"

#include "data/Materials.h"

Garage::Garage(const glm::vec3 position)
	: m_position(position)
{
}

std::vector<SceneObject> Garage::CreateObjects() const
{
	return {
		{ "Garage body",
			{ GeometryType::Box, BodyWidth, BodyDepth, BodyHeight },
			{ m_position },
			Materials::Concrete,
			"assets/concrete.jpg" },
		{ "Garage door",
			{ GeometryType::Box, DoorWidth, DoorThickness, DoorHeight, 2.0f},
			{ { m_position.x, m_position.y + HalfBodyDepth + HalfDoorThickness, m_position.z } },
			Materials::Door,
			"assets/garage-door.png" },
		{ "Garage side window",
			{ GeometryType::Box, WindowThickness, WindowWidth, WindowHeight },
			{ { m_position.x + HalfBodyWidth + HalfWindowThickness, m_position.y, m_position.z + WindowBaseHeight } },
			Materials::Window,
			{} },
		{ "Garage back window",
			{ GeometryType::Box, WindowWidth, WindowThickness, WindowHeight },
			{ { m_position.x, m_position.y - HalfBodyDepth - HalfWindowThickness, m_position.z + WindowBaseHeight } },
			Materials::Window,
			{} }
	};
}
