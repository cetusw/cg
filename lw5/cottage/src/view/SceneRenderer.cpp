#include "view/SceneRenderer.h"

#include "view/GeometryRenderer.h"
#include "view/Texture2D.h"

#include <GL/glew.h>

#include <array>
#include <filesystem>

namespace
{
std::array<GLfloat, 4> ToGlColor(const RgbColor& color, const float alpha = 1.0f)
{
	return { color.red, color.green, color.blue, alpha };
}

std::array<GLfloat, 4> ToGlPoint(const glm::vec3 point)
{
	return { point.x, point.y, point.z, 1.0f };
}
} // namespace

SceneRenderer::SceneRenderer() = default;
SceneRenderer::~SceneRenderer() = default;

void SceneRenderer::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void SceneRenderer::Render(const Scene& scene)
{
	PrepareFrame();
	ConfigureCamera(scene.GetCamera());
	ConfigureLight(scene.GetMainLight());
	DrawObjects(scene.GetObjects());
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
		60.0f,
		aspect,
		0.1f,
		100.0f);

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
	gluLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
}

void SceneRenderer::ConfigureLight(const PointLight& light)
{
	const auto ambient = ToGlColor(light.ambient);
	const auto diffuse = ToGlColor(light.diffuse);
	const auto specular = ToGlColor(light.specular);
	// TODO подумать о том, как перенести параметр направленный или точечный в объект самого света, а не определять его здесь
	const auto position = ToGlPoint(light.position);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient.data());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse.data());
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular.data());
	glLightfv(GL_LIGHT0, GL_POSITION, position.data());
}

void SceneRenderer::ConfigureTexture(const std::string& path)
{
	if (path.empty())
	{
		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
		GetTexture(path).Bind();
	}
}

void SceneRenderer::DrawObjects(const std::vector<SceneObject>& objects)
{
	for (const SceneObject& object : objects)
	{
		DrawObject(object);
	}
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

void SceneRenderer::DrawObject(const SceneObject& object)
{
	ApplyMaterial(object.material);
	ConfigureTexture(object.texturePath);

	glPushMatrix();
	ApplyTransform(object.transform);
	GeometryRenderer::Draw(object.geometry);
	glPopMatrix();
}

Texture2D& SceneRenderer::GetTexture(const std::string& path)
{
	auto iterator = m_textures.find(path);

	if (iterator == m_textures.end())
	{
		const auto texturePath = std::filesystem::path(SOURCE_DIR) / path;
		auto texture = std::make_unique<Texture2D>(texturePath.string());
		iterator = m_textures.emplace(path, std::move(texture)).first;
	}

	return *iterator->second;
}
