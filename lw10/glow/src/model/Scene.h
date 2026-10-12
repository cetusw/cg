#pragma once

#include "model/Cottage.h"
#include "types/Camera.h"
#include "types/Light.h"
#include "types/SceneObject.h"

#include <cstddef>
#include <vector>

class Scene
{
public:
	Scene();

	[[nodiscard]] Camera& GetCamera();
	[[nodiscard]] const Camera& GetCamera() const;
	[[nodiscard]] const PointLight& GetMainLight() const;
	[[nodiscard]] std::size_t GetSpotLightCount() const;
	[[nodiscard]] const SpotLight& GetSpotLight(std::size_t index) const;
	[[nodiscard]] const std::vector<SceneObject>& GetObjects() const;

private:
	Camera m_camera;

	PointLight m_mainLight;
	Cottage m_cottage;

	std::vector<SceneObject> m_objects;
};
