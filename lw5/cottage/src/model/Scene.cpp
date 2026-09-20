#include "model/Scene.h"

namespace Material
{
constexpr MaterialDescription Ground{
	{ 0.10f, 0.20f, 0.10f },
	{ 0.35f, 0.65f, 0.30f },
	{ 0.05f, 0.05f, 0.05f },
	4.0f
};

constexpr MaterialDescription Wall{
	{ 0.30f, 0.10f, 0.08f },
	{ 0.75f, 0.25f, 0.15f },
	{ 0.10f, 0.10f, 0.10f },
	8.0f
};

constexpr MaterialDescription Roof{
	{ 0.15f, 0.15f, 0.15f },
	{ 0.60f, 0.60f, 0.60f },
	{ 0.15f, 0.15f, 0.15f },
	12.0f
};

constexpr MaterialDescription Foundation{
	{ 0.15f, 0.15f, 0.15f },
	{ 0.50f, 0.50f, 0.50f },
	{ 0.10f, 0.10f, 0.10f },
	4.0f
};

constexpr MaterialDescription Window{
	{ 0.10f, 0.15f, 0.20f },
	{ 0.25f, 0.45f, 0.65f },
	{ 0.80f, 0.80f, 0.80f },
	64.0f
};

constexpr MaterialDescription Door{
	{ 0.18f, 0.08f, 0.03f },
	{ 0.45f, 0.20f, 0.08f },
	{ 0.10f, 0.10f, 0.10f },
	8.0f
};
} // namespace Material

namespace Object
{
const SceneObject Ground = {
	"Ground",
	{ GeometryType::Ground, 30.0f, 30.0f, 0.0f, 2.0f },
	{ { 0.0f, 0.0f, 0.0f } },
	Material::Ground,
	"assets/grass.jpg"
};
const SceneObject Foundation = {
	"Foundation",
	{ GeometryType::Box, 7.0f, 5.0f, 0.4f },
	{ { 0.0f, 0.0f, 0.0f } },
	Material::Foundation,
	{}
};

const SceneObject HouseBody = {
	"House body",
	{ GeometryType::Box, 6.0f, 4.0f, 3.0f },
	{ { 0.0f, 0.0f, 0.4f } },
	Material::Wall,
	"assets/brick.jpg"
};

const SceneObject Garage = {
	"Garage",
	{ GeometryType::Box, 3.0f, 4.0f, 2.5f },
	{ { 5.0f, 0.0f, 0.0f } },
	Material::Wall,
	"assets/brick.jpg"
};

const SceneObject GarageDoor = {
	"Garage door",
	{ GeometryType::Box, 2.2f, 0.10f, 2.0f },
	{ { 5.0f, -2.05f, 0.0f } },
	Material::Door,
	{}
};

const SceneObject GarageWindow = {
	"Garage window",
	{ GeometryType::Box, 0.8f, 0.08f, 0.8f },
	{ { 6.54f, 0.0f, 1.1f }, { 0.0f, 0.0f, 90.0f } },
	Material::Window,
	{}
};

const SceneObject Roof = {
	"Roof",
	{ GeometryType::Roof, 6.8f, 4.8f, 1.8f },
	{ { 0.0f, 0.0f, 3.4f } },
	Material::Roof,
	"assets/cobblestone.jpg"
};

const SceneObject LeftHouseWindow = {
	"Left house window",
	{ GeometryType::Box, 1.0f, 0.08f, 1.2f },
	{ { -1.7f, -2.04f, 1.4f } },
	Material::Window,
	{}
};

const SceneObject RightHouseWindow = {
	"Right house window",
	{ GeometryType::Box, 1.0f, 0.08f, 1.2f },
	{ { 1.7f, -2.04f, 1.4f } },
	Material::Window,
	{}
};

const SceneObject HouseDoor = {
	"House door",
	{ GeometryType::Box, 1.2f, 0.10f, 2.2f },
	{ { 0.0f, -2.05f, 0.4f } },
	Material::Door,
	{}
};

} // namespace Object

Scene::Scene()
	: m_camera{
		{ 10.0f, -10.0f, 7.0f },
		{ 0.0f, 0.0f, 1.5f },
		{ 0.0f, 0.0f, 1.0f }
	}
	, m_mainLight{
		{ -5.0f, -5.0f, 8.0f },
		{ 0.2f, 0.2f, 0.2f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f }
	}
	, m_objects{ Object::Ground, Object::Foundation, Object::HouseBody, Object::Garage, Object::Roof, Object::LeftHouseWindow, Object::RightHouseWindow, Object::HouseDoor, Object::GarageDoor, Object::GarageWindow }
{
}

const Camera& Scene::GetCamera() const { return m_camera; }
const PointLight& Scene::GetMainLight() const { return m_mainLight; }
const std::vector<SceneObject>& Scene::GetObjects() const { return m_objects; }
