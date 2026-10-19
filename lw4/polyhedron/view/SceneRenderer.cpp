#include "view/SceneRenderer.h"

#include "view/MeshRenderer.h"

#include <GL/glew.h>
#include <GL/glu.h>

#include <array>

namespace
{
std::array<GLfloat, 4> ToGlColor(const RgbColor& color)
{
	return { color.red, color.green, color.blue, 1.0f };
}

std::array<GLfloat, 4> ToGlPoint(const glm::vec3& point)
{
	return { point.x, point.y, point.z, 1.0f };
}
} // namespace

void SceneRenderer::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void SceneRenderer::SetProjection(const int width, const int height)
{
	if (width <= 0 || height <= 0)
	{
		return;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		60.0,
		static_cast<double>(width) / height,
		0.1,
		100.0);
	glMatrixMode(GL_MODELVIEW);
}

void SceneRenderer::Render(const Scene& scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	const Camera& camera = scene.GetCamera();
	gluLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);

	ApplyMainLight(scene.GetMainLight());
	ApplyMaterial(scene.GetMaterial());
	MeshRenderer::Draw(scene.GetMesh());
}

void SceneRenderer::ApplyMainLight(const PointLight& light)
{
	const auto ambient = ToGlColor(light.ambient);
	const auto diffuse = ToGlColor(light.diffuse);
	const auto specular = ToGlColor(light.specular);
	const auto position = ToGlPoint(light.position);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient.data());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse.data());
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular.data());
	glLightfv(GL_LIGHT0, GL_POSITION, position.data());
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
