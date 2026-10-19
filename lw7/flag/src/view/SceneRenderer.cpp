#include "view/SceneRenderer.h"

#include <GL/glew.h>

#include <glm/vec3.hpp>

#include <filesystem>
#include <glm/vec2.hpp>

SceneRenderer::SceneRenderer()
	: m_shaderProgram(
		  std::filesystem::path(SOURCE_DIR) / "shaders/ring.vert",
		  std::filesystem::path(SOURCE_DIR) / "shaders/ring.frag")
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void SceneRenderer::Render(const int framebufferWidth, const int framebufferHeight)
{
	if (framebufferWidth <= 0 || framebufferHeight <= 0)
	{
		return;
	}

	const float viewportAspectRatio = SetViewport(framebufferWidth, framebufferHeight);
	glDrawBuffer(GL_BACK);
	glDisable(GL_SCISSOR_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	constexpr glm::vec3 backgroundColor(1.0f, 1.0f, 1.0f);
	constexpr glm::vec3 ringColor(0.0f, 0.0f, 0.0f);
	constexpr float innerRadius = 0.15f;
	constexpr float outerRadius = 0.20f;
	constexpr glm::vec2 center(0.5f, 0.5f);

	m_shaderProgram.Use();
	m_shaderProgram.SetVec3Uniform("u_backgroundColor", backgroundColor);
	m_shaderProgram.SetVec3Uniform("u_ringColor", ringColor);
	m_shaderProgram.SetFloatUniform("u_innerRadius", innerRadius);
	m_shaderProgram.SetFloatUniform("u_outerRadius", outerRadius);
	m_shaderProgram.SetFloatUniform("u_viewportAspectRatio", viewportAspectRatio);
	m_shaderProgram.SetVec2Uniform("u_center", center);
	DrawRectangle();
}

float SceneRenderer::SetViewport(const int framebufferWidth, const int framebufferHeight)
{
	glViewport(0, 0, framebufferWidth, framebufferHeight);

	return static_cast<float>(framebufferWidth) / static_cast<float>(framebufferHeight);
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
