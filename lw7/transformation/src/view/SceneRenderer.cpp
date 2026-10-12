#include "view/SceneRenderer.h"

#include "view/ParametricGrid.h"

#include <GL/glew.h>
#include <GL/glu.h>

#include <filesystem>

SceneRenderer::SceneRenderer()
	: m_shaderProgram(
		std::filesystem::path(SOURCE_DIR) / "shaders/morph.vert",
		std::filesystem::path(SOURCE_DIR) / "shaders/morph.frag")
{
}

void SceneRenderer::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.03f, 0.04f, 0.08f, 1.0f);
}

void SceneRenderer::Render(const Camera& camera, const float morph)
{
	PrepareFrame();
	ConfigureCamera(camera);

	m_shaderProgram.Use();
	m_shaderProgram.SetFloatUniform("u_morph", morph);
	ParametricGrid::Draw();
}

void SceneRenderer::SetProjection(const int width, const int height)
{
	const int safeHeight = height <= 0 ? 1 : height;
	const double aspect = static_cast<double>(width) / safeHeight;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspect, 0.1, 100.0);
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
