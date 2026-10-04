#include "model/Lamp.h"

#include "data/Materials.h"

#include <glm/geometric.hpp>

Lamp::Lamp(const glm::vec3 position, const glm::vec3 target)
	: m_position(position)
	, m_light(CreateLight(position, target))
{
}

const SpotLight& Lamp::GetLight() const
{
	return m_light;
}

glm::vec3 Lamp::GetLightPosition(const glm::vec3& position)
{
	return { position.x, position.y, position.z + Height };
}

SpotLight Lamp::CreateLight(
	const glm::vec3& position,
	const glm::vec3& target)
{
	const glm::vec3 lightPosition = GetLightPosition(position);

	return {
		lightPosition,
		glm::normalize(target - lightPosition),
		{ 0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.9f, 0.7f },
		{ 1.0f, 0.9f, 0.7f },
		45.0f,
		0.0f
	};
}

std::vector<SceneObject> Lamp::CreateObjects() const
{
	return {
		{ "Lamp base",
			{ GeometryType::Box, BaseWidth, BaseDepth, BaseHeight },
			{ m_position },
			Materials::Metal,
			{} },
		{ "Lamp post",
			{ GeometryType::Box, PostWidth, PostDepth, PostHeight },
			{ { m_position.x, m_position.y, m_position.z + BaseHeight } },
			Materials::Metal,
			{} },
		{ "Lamp head",
			{ GeometryType::Box, HeadWidth, HeadDepth, HeadHeight },
			{ { m_position.x, m_position.y, m_position.z + Height - HalfHeadHeight } },
			Materials::Metal,
			{} }
	};
}
