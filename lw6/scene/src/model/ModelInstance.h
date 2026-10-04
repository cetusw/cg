#pragma once

#include "types/LinearMovement.h"
#include "types/Transform.h"

#include <memory>
#include <optional>

class Model3ds;

class ModelInstance
{
public:
	ModelInstance(std::shared_ptr<Model3ds> model, Transform transform);

	void SetLinearMovement(LinearMovement movement);
	void Update(float deltaTime);

	[[nodiscard]] const Model3ds& GetModel() const;
	[[nodiscard]] const Transform& GetTransform() const;

private:
	std::shared_ptr<Model3ds> m_model;
	Transform m_transform;
	std::optional<LinearMovement> m_movement;
};
