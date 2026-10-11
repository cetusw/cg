#include "view/SceneRenderer.h"

#include <GL/glew.h>

#include <filesystem>

SceneRenderer::SceneRenderer()
	: m_shaderProgram(
		  std::filesystem::path(SOURCE_DIR) / "shaders/wave.vert",
		  std::filesystem::path(SOURCE_DIR) / "shaders/wave.frag")
	, m_textureFrom(std::filesystem::path(SOURCE_DIR) / "textures/water.jpeg")
	, m_textureTo(std::filesystem::path(SOURCE_DIR) / "textures/gorin.jpg")
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void SceneRenderer::Render(
	const glm::vec2 center,
	const float elapsedTime,
	const bool isWaveActive,
	const float aspectRatio)
{
	PrepareFrame();

	m_shaderProgram.Use();

	m_textureFrom.BindToUnit(0);
	m_textureTo.BindToUnit(1);

	m_shaderProgram.SetIntUniform("u_textureFrom", 0);
	m_shaderProgram.SetIntUniform("u_textureTo", 1);
	m_shaderProgram.SetVec2Uniform("u_center", center);
	m_shaderProgram.SetFloatUniform("u_elapsedTime", elapsedTime);
	m_shaderProgram.SetIntUniform("u_isWaveActive", isWaveActive ? 1 : 0);
	m_shaderProgram.SetFloatUniform("u_aspectRatio", aspectRatio);

	DrawRectangle();
}

void SceneRenderer::PrepareFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void SceneRenderer::DrawRectangle()
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd();
}
