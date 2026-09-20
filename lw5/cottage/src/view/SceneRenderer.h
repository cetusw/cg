#pragma once

#include "model/Scene.h"

#include <memory>
#include <string>
#include <unordered_map>

class Texture2D;

class SceneRenderer
{
public:
	SceneRenderer();
	~SceneRenderer();

	void Initialize();
	void Render(const Scene& scene);

private:
	void ConfigureLight(const PointLight& light) const;
	void ApplyMaterial(const MaterialDescription& material) const;
	void DrawObject(const SceneObject& object);
	void DrawGeometry(const GeometryDescription& geometry) const;
	void DrawBox(const GeometryDescription& geometry) const;
	void DrawGround(const GeometryDescription& geometry) const;
	void DrawRoof(const GeometryDescription& geometry) const;
	Texture2D& GetTexture(const std::string& path);

	std::unordered_map<std::string, std::unique_ptr<Texture2D>> m_textures;
};
