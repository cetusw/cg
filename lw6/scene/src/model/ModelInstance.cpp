#include "model/ModelInstance.h"

#include "model/Model3ds.h"

#include <glm/geometric.hpp>

#include <utility>

ModelInstance::ModelInstance(std::shared_ptr<Model3ds> model, Transform transform)
	: m_model(std::move(model))
	, m_transform(transform)
{
}

void ModelInstance::SetLinearMovement(LinearMovement movement)
{
	m_transform.position = movement.start;
	m_movement = movement;
}

void ModelInstance::Update(const float deltaTime)
{
	if (!m_movement.has_value())
	{
		return;
	}

	LinearMovement& movement = *m_movement;
	const glm::vec3 target = movement.isMovingToEnd
		? movement.end
		: movement.start;
	const glm::vec3 offset = target - m_transform.position;
	const float distance = glm::length(offset);
	const float step = movement.speed * deltaTime;

	if (step >= distance)
	{
		m_transform.position = target;
		movement.isMovingToEnd = !movement.isMovingToEnd;
		return;
	}

	m_transform.position += glm::normalize(offset) * step;
}

const Model3ds& ModelInstance::GetModel() const
{
	return *m_model;
}

const Transform& ModelInstance::GetTransform() const
{
	return m_transform;
}
