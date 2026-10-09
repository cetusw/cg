#include "view/SceneRenderer.h"

#include <GL/glew.h>

#include <filesystem>

SceneRenderer::SceneRenderer()
	: m_shaderProgram(
		  std::filesystem::path(SOURCE_DIR) / "shaders/wave.vert",
		  std::filesystem::path(SOURCE_DIR) / "shaders/wave.frag")
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void SceneRenderer::Render(const float time)
{
	PrepareFrame();
	m_shaderProgram.Use();
	m_shaderProgram.SetFloatUniform("u_time", time);
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
