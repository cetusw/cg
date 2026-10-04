#pragma once

#include "model/ModelInstance.h"
#include "types/Camera.h"
#include "types/Light.h"

#include <vector>

class Scene
{
public:
	Scene();

	void Update(float deltaTime);

	[[nodiscard]] Camera& GetCamera();
	[[nodiscard]] const Camera& GetCamera() const;
	[[nodiscard]] const PointLight& GetMainLight() const;
	[[nodiscard]] const std::vector<ModelInstance>& GetModels() const;

private:
	Camera m_camera;
	PointLight m_mainLight;
	std::vector<ModelInstance> m_models;
};
