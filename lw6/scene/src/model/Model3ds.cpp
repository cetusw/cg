#include "model/Model3ds.h"

#include <lib3ds/file.h>
#include <lib3ds/mesh.h>

#include <memory>
#include <stdexcept>

Model3ds::Model3ds(const std::filesystem::path& path)
	: m_directory(path.parent_path())
{
	m_file = lib3ds_file_load(path.string().c_str());
	if (m_file == nullptr)
	{
		throw std::runtime_error("Failed to load 3ds model: " + path.string());
	}

	CalculateNormals();
}

Model3ds::~Model3ds()
{
	if (m_file != nullptr)
	{
		lib3ds_file_free(m_file);
	}
}

const Lib3dsFile& Model3ds::GetFile() const
{
	return *m_file;
}

const std::vector<glm::vec3>& Model3ds::GetNormals(const Lib3dsMesh& mesh) const
{
	return m_normals.at(&mesh);
}

std::filesystem::path Model3ds::ResolveTexturePath(const char* textureName) const
{
	return m_directory / textureName;
}

void Model3ds::CalculateNormals()
{
	for (Lib3dsMesh* mesh = m_file->meshes; mesh != nullptr; mesh = mesh->next)
	{
		auto& normals = m_normals[mesh];
		normals.resize(mesh->faces * VERTICES_PER_FACE);

		const auto calculatedNormals = std::make_unique<Lib3dsVector[]>(mesh->faces * VERTICES_PER_FACE);
		lib3ds_mesh_calculate_normals(mesh, calculatedNormals.get());

		for (std::size_t normalIndex = 0; normalIndex < normals.size(); ++normalIndex)
		{
			normals[normalIndex] = {
				calculatedNormals[normalIndex][0],
				calculatedNormals[normalIndex][1],
				calculatedNormals[normalIndex][2]
			};
		}
	}
}
