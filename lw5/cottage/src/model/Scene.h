#pragma once

#include <string>
#include <vector>

struct Vector3
{
	float x{};
	float y{};
	float z{};
};

struct RgbColor
{
	float red{};
	float green{};
	float blue{};
};

struct MaterialDescription
{
	RgbColor ambient;
	RgbColor diffuse;
	RgbColor specular;

	float shininess{};
	float opacity = 1.0f;
};

enum class GeometryType
{
	Box,
	TriangularPrism,
	Plane
};

struct GeometryDescription
{
	GeometryType type{};
	float width{};
	float depth{};
	float height{};
	float textureScale = 1.0f;
};

struct Transform
{
	Vector3 position;
	Vector3 rotation{
		0.0f,
		0.0f,
		0.0f
	};
	Vector3 scale{
		1.0f,
		1.0f,
		1.0f
	};
};

struct SceneObject
{
	std::string name;
	GeometryDescription geometry;
	Transform transform;
	MaterialDescription material;
	std::string texturePath;
};

struct PointLight
{
	Vector3 position;
	RgbColor ambient;
	RgbColor diffuse;
	RgbColor specular;
};

struct Camera
{
	Vector3 position;
	Vector3 target;
	Vector3 up;
};

class Scene
{
public:
	Scene();

	[[nodiscard]] Camera& GetCamera();
	[[nodiscard]] const Camera& GetCamera() const;
	[[nodiscard]] const PointLight& GetMainLight() const;
	[[nodiscard]] const std::vector<SceneObject>& GetObjects() const;

private:
	Camera m_camera;
	PointLight m_mainLight;
	std::vector<SceneObject> m_objects;
};
