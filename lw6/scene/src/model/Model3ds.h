#pragma once

#include <filesystem>
#include <unordered_map>
#include <vector>

#include <glm/vec3.hpp>

struct Lib3dsFile;
struct Lib3dsMesh;

class Model3ds
{
public:
	explicit Model3ds(const std::filesystem::path& path);
	~Model3ds();

	Model3ds(const Model3ds&) = delete;
	Model3ds& operator=(const Model3ds&) = delete;

	[[nodiscard]] const Lib3dsFile& GetFile() const;
	[[nodiscard]] const std::vector<glm::vec3>& GetNormals(const Lib3dsMesh& mesh) const;
	[[nodiscard]] std::filesystem::path ResolveTexturePath(const char* textureName) const;

	static constexpr std::size_t VERTICES_PER_FACE = 3;

private:
	void CalculateNormals();

	Lib3dsFile* m_file = nullptr;
	std::filesystem::path m_directory;
	std::unordered_map<const Lib3dsMesh*, std::vector<glm::vec3>> m_normals;
};
