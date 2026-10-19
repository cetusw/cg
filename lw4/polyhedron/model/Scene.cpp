#include "model/Scene.h"

#include <utility>

namespace
{
constexpr Camera DefaultCamera{
	{ 0.0f, 5.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f }
};

constexpr PointLight DefaultMainLight{
	{ 5.0f, 5.0f, 5.0f },
	{ 0.2f, 0.2f, 0.2f },
	{ 0.85f, 0.85f, 0.85f },
	{ 0.6f, 0.6f, 0.6f }
};

constexpr MaterialDescription DefaultMaterial{
	{ 0.3f, 0.3f, 0.3f },
	{ 0.9f, 0.9f, 0.9f },
	{ 0.8f, 0.8f, 0.8f },
	100.0f
};
} // namespace

Scene::Scene(Mesh mesh)
	: m_camera(DefaultCamera)
	, m_mesh(std::move(mesh))
	, m_mainLight(DefaultMainLight)
	, m_material(DefaultMaterial)
{
}

Camera& Scene::GetCamera()
{
	return m_camera;
}

const Camera& Scene::GetCamera() const
{
	return m_camera;
}

const Mesh& Scene::GetMesh() const
{
	return m_mesh;
}

const PointLight& Scene::GetMainLight() const
{
	return m_mainLight;
}

const MaterialDescription& Scene::GetMaterial() const
{
	return m_material;
}

bool Scene::IsTransparent() const
{
	return m_isTransparent;
}

void Scene::ToggleTransparency()
{
	m_isTransparent = !m_isTransparent;
}
