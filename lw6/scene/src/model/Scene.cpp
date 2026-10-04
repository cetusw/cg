#include "model/Scene.h"

#include "model/Model3ds.h"

#include <filesystem>
#include <memory>

namespace
{
constexpr Camera DefaultCamera{
	{ 18.0f, -22.0f, 16.0f },
	{ 0.0f, 0.0f, 2.0f },
	{ 0.0f, 0.0f, 1.0f }
};

constexpr PointLight DefaultMainLight{
	{ -8.0f, -6.0f, 16.0f },
	{ 0.2f, 0.2f, 0.2f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f }
};

constexpr char CarModelPath[] = "assets/car/BMW_M3_GTR.3ds";

std::shared_ptr<Model3ds> LoadModel(const char* path)  // TODO в чём смысл этой функции и почему она находится в Scene?
{
	return std::make_shared<Model3ds>(
		std::filesystem::path(SOURCE_DIR) / path);
}
} // namespace

Scene::Scene()
	: m_camera(DefaultCamera)
	, m_mainLight(DefaultMainLight)
{
	const auto car = LoadModel(CarModelPath);

	m_models.emplace_back(car, Transform{ { 0.0f, -9.0f, 0.0f }, { 0.0f, 0.0f, 90.0f }, { 0.015f, 0.015f, 0.015f } });
	m_models.back().SetLinearMovement({ { 0.0f, -9.0f, 0.0f }, { 0.0f, 9.0f, 0.0f }, 3.0f });
}

void Scene::Update(const float deltaTime)
{
	for (ModelInstance& model : m_models)
	{
		model.Update(deltaTime);
	}
}

Camera& Scene::GetCamera()
{
	return m_camera;
}

const Camera& Scene::GetCamera() const
{
	return m_camera;
}

const PointLight& Scene::GetMainLight() const
{
	return m_mainLight;
}

const std::vector<ModelInstance>& Scene::GetModels() const
{
	return m_models;
}
