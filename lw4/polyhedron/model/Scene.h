#pragma once

#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Mesh.h"

class Scene
{
public:
	explicit Scene(Mesh mesh);

	[[nodiscard]] Camera& GetCamera();
	[[nodiscard]] const Camera& GetCamera() const;
	[[nodiscard]] const Mesh& GetMesh() const;
	[[nodiscard]] const PointLight& GetMainLight() const;
	[[nodiscard]] const MaterialDescription& GetMaterial() const;
	[[nodiscard]] bool IsTransparent() const;
	void ToggleTransparency();

private:
	Camera m_camera;
	Mesh m_mesh;
	PointLight m_mainLight;
	MaterialDescription m_material;
	bool m_isTransparent = true;
};
