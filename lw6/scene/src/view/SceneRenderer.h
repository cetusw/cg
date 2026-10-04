#pragma once

#include "model/Scene.h"

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

struct Lib3dsFace;
struct Lib3dsFile;
struct Lib3dsMaterial;
struct Lib3dsMesh;
class Model3ds;
class ModelInstance;
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
	void DrawModels(const std::vector<ModelInstance>& models);
	void DrawModel(const ModelInstance& instance);
	void DrawMesh(const Model3ds& model, const Lib3dsMesh& mesh);
	void DrawFace(const Model3ds& model, const Lib3dsMesh& mesh, const Lib3dsFace& face, std::size_t faceIndex);
	void ConfigureTexture(const std::filesystem::path& path);
	Texture2D* GetTexture(const std::filesystem::path& path);

	static glm::vec3 GetNormal(const std::vector<glm::vec3>& normals, size_t faceIndex, size_t vertexInFace);

	static void ApplyMaterial(const MaterialDescription& material);
	static void ApplyTransform(const Transform& transform);
	static MaterialDescription GetMaterialDescription(const Lib3dsMaterial& material);
	static const Lib3dsMaterial* FindMaterial(const Lib3dsFile& file, const Lib3dsFace& face);

	std::unordered_map<std::string, std::unique_ptr<Texture2D>> m_textures;
	std::unordered_set<std::string> m_missingTextures;
};
