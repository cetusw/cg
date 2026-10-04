#include "view/SceneRenderer.h"

#include "model/Model3ds.h"
#include "model/ModelInstance.h"
#include "view/Texture2D.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <lib3ds/file.h>
#include <lib3ds/material.h>
#include <lib3ds/mesh.h>

#include <algorithm>
#include <array>
#include <cstring>
#include <stdexcept>

namespace
{
constexpr MaterialDescription FallbackMaterial{
	{ 0.12f, 0.12f, 0.12f },
	{ 0.65f, 0.65f, 0.65f },
	{ 0.10f, 0.10f, 0.10f },
	8.0f
};

std::array<GLfloat, 4> ToGlColor(const RgbColor& color)
{
	return { color.red, color.green, color.blue, 1.0f };
}
} // namespace

SceneRenderer::SceneRenderer() = default;
SceneRenderer::~SceneRenderer() = default;

void SceneRenderer::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void SceneRenderer::Render(const Scene& scene)
{
	PrepareFrame();
	ConfigureCamera(scene.GetCamera());
	ConfigureLight(scene.GetMainLight());
	DrawModels(scene.GetModels());
	glDisable(GL_TEXTURE_2D);
}

void SceneRenderer::SetProjection(const int width, const int height)
{
	const int safeHeight = height <= 0
		? 1
		: height;

	const double aspect = static_cast<double>(width) / safeHeight;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(
		60.0,
		aspect,
		0.1,
		100.0);

	glMatrixMode(GL_MODELVIEW);
}

void SceneRenderer::PrepareFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SceneRenderer::ConfigureCamera(const Camera& camera)
{
	gluLookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
}

void SceneRenderer::ConfigureLight(const PointLight& light)
{
	const auto ambient = ToGlColor(light.ambient);
	const auto diffuse = ToGlColor(light.diffuse);
	const auto specular = ToGlColor(light.specular);
	const std::array position{ light.position.x, light.position.y, light.position.z, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient.data());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse.data());
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular.data());
	glLightfv(GL_LIGHT0, GL_POSITION, position.data());
}

void SceneRenderer::DrawModels(const std::vector<ModelInstance>& models)
{
	for (const ModelInstance& model : models)
	{
		DrawModel(model);
	}
}

void SceneRenderer::DrawModel(const ModelInstance& instance)
{
	const Model3ds& model = instance.GetModel();
	glPushMatrix();
	ApplyTransform(instance.GetTransform());
	for (const Lib3dsMesh* mesh = model.GetFile().meshes; mesh != nullptr; mesh = mesh->next)
	{
		DrawMesh(model, *mesh);
	}
	glPopMatrix();
}

void SceneRenderer::DrawMesh(const Model3ds& model, const Lib3dsMesh& mesh)
{
	for (std::size_t faceIndex = 0; faceIndex < mesh.faces; ++faceIndex) // TODO вспомнить, почему здесь можно префиксный ++ и в чём вообще разница
	{
		DrawFace(model, mesh, mesh.faceL[faceIndex], faceIndex);
	}
}

void SceneRenderer::DrawFace(
	const Model3ds& model,
	const Lib3dsMesh& mesh,
	const Lib3dsFace& face,
	const std::size_t faceIndex)
{
	const Lib3dsMaterial* material = FindMaterial(model.GetFile(), face);
	ApplyMaterial(material == nullptr
			? FallbackMaterial
			: GetMaterialDescription(*material));
	ConfigureTexture(material == nullptr || material->texture1_map.name[0] == '\0'
			? std::filesystem::path{}
			: model.ResolveTexturePath(material->texture1_map.name));

	const std::vector<glm::vec3>& normals = model.GetNormals(mesh);

	glBegin(GL_TRIANGLES);
	for (std::size_t vertexInFace = 0; vertexInFace < Model3ds::VERTICES_PER_FACE; ++vertexInFace)
	{
		const glm::vec3 normal = GetNormal(normals, faceIndex, vertexInFace);
		glNormal3f(normal.x, normal.y, normal.z);

		const std::size_t vertexIndex = face.points[vertexInFace];

		if (mesh.texelL != nullptr && vertexIndex < mesh.texels)
		{
			const float u = mesh.texelL[vertexIndex][0];
			const float v = mesh.texelL[vertexIndex][1];
			glTexCoord2f(u, v);
		}

		const Lib3dsPoint& point = mesh.pointL[vertexIndex];
		glVertex3f(point.pos[0], point.pos[1], point.pos[2]);
	}
	glEnd();
}

void SceneRenderer::ConfigureTexture(const std::filesystem::path& path)
{
	const Texture2D* texture = GetTexture(path);
	if (texture == nullptr)
	{
		glDisable(GL_TEXTURE_2D);
		return;
	}
	glEnable(GL_TEXTURE_2D);
	texture->Bind();
}

Texture2D* SceneRenderer::GetTexture(const std::filesystem::path& path)
{
	if (path.empty())
	{
		return nullptr;
	}

	const std::string texturePath = path.string();
	if (m_missingTextures.contains(texturePath))
	{
		return nullptr;
	}
	const auto iterator = m_textures.find(texturePath);
	if (iterator != m_textures.end())
	{
		return iterator->second.get();
	}

	try
	{
		return m_textures.emplace(texturePath, std::make_unique<Texture2D>(texturePath)).first->second.get();
	}
	catch (const std::runtime_error&)
	{
		m_missingTextures.insert(texturePath);
		return nullptr;
	}
}

glm::vec3 SceneRenderer::GetNormal(
	const std::vector<glm::vec3>& normals,
	const std::size_t faceIndex,
	const std::size_t vertexInFace)
{
	const std::size_t faceNormalsStart = faceIndex * Model3ds::VERTICES_PER_FACE;
	const std::size_t normalIndex = faceNormalsStart + vertexInFace;
	return normals[normalIndex];
}

void SceneRenderer::ApplyMaterial(const MaterialDescription& material)
{
	const auto ambient = ToGlColor(material.ambient);
	const auto diffuse = ToGlColor(material.diffuse);
	const auto specular = ToGlColor(material.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient.data());
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse.data());
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular.data());
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);
}

void SceneRenderer::ApplyTransform(const Transform& transform)
{
	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
	glRotatef(transform.rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(transform.rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(transform.rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
}

MaterialDescription SceneRenderer::GetMaterialDescription(const Lib3dsMaterial& material)
{
	constexpr float minOpenGlShininess = 0.0f;
	constexpr float maxOpenGlShininess = 128.0f;
	return {
		{ material.ambient[0], material.ambient[1], material.ambient[2] },
		{ material.diffuse[0], material.diffuse[1], material.diffuse[2] },
		{ material.specular[0], material.specular[1], material.specular[2] },
		std::clamp(material.shininess * maxOpenGlShininess, minOpenGlShininess, maxOpenGlShininess)
	};
}

const Lib3dsMaterial* SceneRenderer::FindMaterial(const Lib3dsFile& file, const Lib3dsFace& face)
{
	if (face.material[0] == '\0')
	{
		return nullptr;
	}
	for (const Lib3dsMaterial* material = file.materials; material != nullptr; material = material->next)
	{
		if (std::strcmp(material->name, face.material) == 0)
		{
			return material;
		}
	}
	return nullptr;
}
