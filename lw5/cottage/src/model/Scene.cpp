#include "model/Scene.h"

#include "model/Cottage.h"
#include "model/Materials.h"

Scene::Scene()
	: m_camera{
		{ 10.0f, 10.0f, 7.0f },
		{ 0.0f, 0.0f, 1.5f },
		{ 0.0f, 0.0f, 1.0f }
	}
	, m_mainLight{
		{ -5.0f, 5.0f, 8.0f },
		{ 0.2f, 0.2f, 0.2f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f }
	}
	, m_objects{
		{ "Ground",
			{ GeometryType::Ground, 30.0f, 30.0f, 0.0f, 2.0f },
			{ { 0.0f, 0.0f, -0.01f } },
			Materials::Ground,
			"assets/grass.jpg" }
	}
{
	const Cottage cottage({ 0.0f, 0.0f, 0.0f });
	const std::vector<SceneObject> cottageObjects = cottage.CreateObjects();

	m_objects.insert(
		m_objects.end(),
		cottageObjects.begin(),
		cottageObjects.end());
}

Camera& Scene::GetCamera() { return m_camera; }
const Camera& Scene::GetCamera() const { return m_camera; }
const PointLight& Scene::GetMainLight() const { return m_mainLight; }
const std::vector<SceneObject>& Scene::GetObjects() const { return m_objects; }
