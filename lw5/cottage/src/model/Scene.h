#pragma once

#include "types/Camera.h"
#include "types/Light.h"
#include "types/SceneObject.h"

#include <vector>

class Scene
{
public:
	Scene();

	[[nodiscard]] Camera& GetCamera();
	[[nodiscard]] const Camera& GetCamera() const;
	[[nodiscard]] const PointLight& GetMainLight() const;
	[[nodiscard]] const std::vector<SpotLight>& GetSpotLights() const;
	[[nodiscard]] const std::vector<SceneObject>& GetObjects() const;

private:
	Camera m_camera;

	PointLight m_mainLight;
	std::vector<SpotLight> m_spotLights;

	std::vector<SceneObject> m_objects;
};
