#include "view/SceneRenderer.h"

#include <GL/glew.h>

#include <algorithm>
#include <cmath>
#include <filesystem>

SceneRenderer::SceneRenderer()
	: m_shaderProgram(
		  std::filesystem::path(SOURCE_DIR) / "shaders/wave.vert",
		  std::filesystem::path(SOURCE_DIR) / "shaders/wave.frag")
	, m_textureFrom(std::filesystem::path(SOURCE_DIR) / "textures/water.jpeg")
	, m_textureTo(std::filesystem::path(SOURCE_DIR) / "textures/turtle.jpg")
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void SceneRenderer::Render(
	const glm::vec2 center,
	const float elapsedTime,
	const bool isWaveActive,
	const int framebufferWidth,
	const int framebufferHeight)
{
	const Viewport viewport = CalculateViewport(framebufferWidth, framebufferHeight);

	glViewport(0, 0, framebufferWidth, framebufferHeight);
	PrepareFrame();

	if (viewport.width == 0 || viewport.height == 0)
	{
		return;
	}

	glViewport(viewport.x, viewport.y, viewport.width, viewport.height);

	m_shaderProgram.Use();

	m_textureFrom.BindToUnit(0);
	m_shaderProgram.SetIntUniform("u_textureFrom", 0);
	m_textureTo.BindToUnit(1);
	m_shaderProgram.SetIntUniform("u_textureTo", 1);

	m_shaderProgram.SetVec2Uniform("u_center", center);
	m_shaderProgram.SetFloatUniform("u_elapsedTime", elapsedTime);
	m_shaderProgram.SetIntUniform("u_isWaveActive", isWaveActive ? 1 : 0);
	m_shaderProgram.SetFloatUniform(
		"u_aspectRatio",
		static_cast<float>(viewport.width) / static_cast<float>(viewport.height));

	DrawRectangle();
}

bool SceneRenderer::TryGetTextureCoordinates(
	const glm::dvec2 framebufferPosition,
	const int framebufferWidth,
	const int framebufferHeight,
	glm::vec2& textureCoordinates) const
{
	const Viewport viewport = CalculateViewport(framebufferWidth, framebufferHeight);
	if (viewport.width == 0 || viewport.height == 0 ||
		framebufferPosition.x < viewport.x ||
		framebufferPosition.x > viewport.x + viewport.width ||
		framebufferPosition.y < viewport.y ||
		framebufferPosition.y > viewport.y + viewport.height)
	{
		return false;
	}

	textureCoordinates = {
		static_cast<float>((framebufferPosition.x - viewport.x) / viewport.width),
		static_cast<float>((framebufferPosition.y - viewport.y) / viewport.height)
	};
	return true;
}

void SceneRenderer::SwapTextures()
{
	std::swap(m_textureFrom, m_textureTo);
}

SceneRenderer::Viewport SceneRenderer::CalculateViewport(
	const int framebufferWidth,
	const int framebufferHeight) const
{
	const glm::ivec2 textureSize = m_textureFrom.GetSize();
	if (framebufferWidth <= 0 || framebufferHeight <= 0 ||
		textureSize.x <= 0 || textureSize.y <= 0)
	{
		return {};
	}

	const float scale = std::min(
		static_cast<float>(framebufferWidth) / static_cast<float>(textureSize.x),
		static_cast<float>(framebufferHeight) / static_cast<float>(textureSize.y));

	const int viewportWidth = std::max(1, static_cast<int>(std::floor(textureSize.x * scale)));
	const int viewportHeight = std::max(1, static_cast<int>(std::floor(textureSize.y * scale)));
	return {
		(framebufferWidth - viewportWidth) / 2,
		(framebufferHeight - viewportHeight) / 2,
		viewportWidth,
		viewportHeight
	};
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
