#include "model/Cottage.h"

#include "model/Materials.h"

Cottage::Cottage(const Vector3 position)
	: m_position(position)
{
}

std::vector<SceneObject> Cottage::CreateObjects() const
{
	return {
		{ "Foundation",
			{ GeometryType::Box, 7.0f, 5.0f, 0.4f },
			{ m_position },
			Materials::Foundation,
			{} },
		{ "House body",
			{ GeometryType::Box, 6.0f, 4.0f, 3.0f },
			{ { m_position.x, m_position.y, m_position.z + 0.4f } },
			Materials::Wall,
			"assets/brick.jpg" },
		{ "Roof",
			{ GeometryType::Roof, 6.8f, 4.8f, 1.8f },
			{ { m_position.x, m_position.y, m_position.z + 3.4f } },
			Materials::Roof,
			"assets/cobblestone.jpg" },
		{ "Left house window",
			{ GeometryType::Box, 1.0f, 0.08f, 1.2f },
			{ { m_position.x - 1.7f, m_position.y - 2.04f, m_position.z + 1.4f } },
			Materials::Window,
			{} },
		{ "Right house window",
			{ GeometryType::Box, 1.0f, 0.08f, 1.2f },
			{ { m_position.x + 1.7f, m_position.y - 2.04f, m_position.z + 1.4f } },
			Materials::Window,
			{} },
		{ "House door",
			{ GeometryType::Box, 1.2f, 0.10f, 2.2f },
			{ { m_position.x, m_position.y - 2.05f, m_position.z + 0.4f } },
			Materials::Door,
			{} }
	};
}
