#include "view/SceneRenderer.h"

#include "view/ParametricCurve.h"

#include <GL/glew.h>
#include <GL/glu.h>

#include <filesystem>

namespace
{
constexpr double HalfViewSize = 2.1;
constexpr double ViewCenterY = 0.35;
}

SceneRenderer::SceneRenderer()
	: m_shaderProgram(
		std::filesystem::path(SOURCE_DIR) / "shaders/canabola.vert",
		std::filesystem::path(SOURCE_DIR) / "shaders/canabola.frag")
{
}

void SceneRenderer::Initialize()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glClearColor(0.03f, 0.04f, 0.08f, 1.0f);
	glLineWidth(2.0f);
}

void SceneRenderer::Render(const Camera& camera)
{
	PrepareFrame();
	ConfigureCamera(camera);

	m_shaderProgram.Use();
	ParametricCurve::Draw();
}

void SceneRenderer::SetProjection(const int width, const int height)
{
	const int safeHeight = height <= 0 ? 1 : height;
	const double aspect = static_cast<double>(width) / safeHeight;

	const double halfWidth = aspect >= 1.0 ? HalfViewSize * aspect : HalfViewSize;
	const double halfHeight = aspect >= 1.0 ? HalfViewSize : HalfViewSize / aspect;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		-halfWidth, halfWidth,
		ViewCenterY - halfHeight, ViewCenterY + halfHeight,
		-2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
}

void SceneRenderer::PrepareFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
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
