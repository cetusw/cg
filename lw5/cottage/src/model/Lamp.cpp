#include "Lamp.h"

#include "data/Materials.h"

Lamp::Lamp(const glm::vec3 position)
	: m_position(position)
{
}

std::vector<SceneObject> Lamp::CreateObjects() const
{
	return {
		{ "Pillar",
			{ GeometryType::Box, 0.1f, 0.1f, 2.5f },
			{ m_position },
			Materials::Metal,
			"assets/metal.jpg" },
		{ "Lamp",
			{ GeometryType::Box, 0.5f, 0.1f, 0.1f },
			{ { m_position.x + 0.2f, m_position.y, m_position.z + 2.5f },
				{ 0.0f, -20.0f, 0.0f } },
			Materials::Metal,
			"assets/metal.jpg" },
	};
}