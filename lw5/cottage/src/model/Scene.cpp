#include "model/Scene.h"

#include "data/Materials.h"
#include "model/Cottage.h"

namespace
{
constexpr glm::vec3 DefaultCameraPosition{
	10.0f,
	10.0f,
	7.0f
};

constexpr glm::vec3 DefaultCameraTarget{
	0.0f,
	0.0f,
	1.5f
};

constexpr glm::vec3 DefaultCameraUp{
	0.0f,
	0.0f,
	1.0f
};

constexpr glm::vec3 DefaultMainLightPosition{
	-5.0f,
	5.0f,
	8.0f
};

constexpr RgbColor DefaultMainLightAmbient{
	0.2f,
	0.2f,
	0.2f
};

constexpr RgbColor DefaultMainLightDiffuse{
	1.0f,
	1.0f,
	1.0f
};

constexpr RgbColor DefaultMainLightSpecular{
	1.0f,
	1.0f,
	1.0f
};

constexpr float GroundWidth = 30.0f;
constexpr float GroundDepth = 30.0f;
constexpr float GroundHeight = 0.0f;
constexpr float GroundTextureScale = 1.0f;
constexpr glm::vec3 GroundPosition{
	0.0f,
	0.0f,
	-0.01f
};
constexpr char GroundTexturePath[] = "assets/grass.jpg";

constexpr glm::vec3 DefaultCottagePosition{
	0.0f,
	0.0f,
	0.0f
};

Camera CreateDefaultCamera()
{
	return {
		DefaultCameraPosition,
		DefaultCameraTarget,
		DefaultCameraUp
	};
}

PointLight CreateDefaultMainLight()
{
	return {
		DefaultMainLightPosition,
		DefaultMainLightAmbient,
		DefaultMainLightDiffuse,
		DefaultMainLightSpecular
	};
}

SceneObject CreateGround()
{
	return {
		"Ground",
		{ GeometryType::Plane,
			GroundWidth,
			GroundDepth,
			GroundHeight,
			GroundTextureScale },
		{ GroundPosition },
		Materials::Ground,
		GroundTexturePath
	};
}
} // namespace

Scene::Scene()
	: m_camera(CreateDefaultCamera())
	, m_mainLight(CreateDefaultMainLight())
	, m_objects{ CreateGround() }
{
	const Cottage cottage(DefaultCottagePosition);
	const std::vector<SceneObject> cottageObjects = cottage.CreateObjects();

	m_objects.insert(
		m_objects.end(),
		cottageObjects.begin(),
		cottageObjects.end());
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

const std::vector<SceneObject>& Scene::GetObjects() const
{
	return m_objects;
}
