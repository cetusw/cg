#include "model/Garage.h"

#include "model/Materials.h"

Garage::Garage(const Vector3 position)
	: m_position(position)
{
}

std::vector<SceneObject> Garage::CreateObjects() const
{
	return {
		{ "Garage body",
			{ GeometryType::Box, 4.0f, 4.0f, 2.0f },
			{ m_position },
			Materials::Wall,
			"assets/brick.jpg" },
		{ "Garage door",
			{ GeometryType::Box, 2.0f, 0.10f, 2.0f },
			{ { m_position.x, m_position.y - 2.05f, m_position.z } },
			Materials::Door,
			{} },
		{ "Garage window",
			{ GeometryType::Box, 0.10f, 2.0f, 1.0f },
			{ { m_position.x + 2.05f, m_position.y, m_position.z + 0.5f } },
			Materials::Window,
			{} }
	};
}
