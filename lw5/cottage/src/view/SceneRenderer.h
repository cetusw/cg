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

	static void Initialize();
	void Render(const Scene& scene);
	static void SetProjection(int width, int height);

private:
	static void PrepareFrame();
	static void ConfigureCamera(const Camera& camera);
	static void ConfigureLight(const PointLight& light);
	void ConfigureTexture(const std::string& path);

	void DrawObjects(const std::vector<SceneObject>& objects);

	static void ApplyMaterial(const MaterialDescription& material);
	static void ApplyTransform(const Transform& transform);

	void DrawObject(const SceneObject& object);

	Texture2D& GetTexture(const std::string& path);

	std::unordered_map<std::string, std::unique_ptr<Texture2D>> m_textures;
};
