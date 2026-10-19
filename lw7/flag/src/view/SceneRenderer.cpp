#include "view/SceneRenderer.h"

#include <GL/glew.h>

#include <filesystem>

SceneRenderer::SceneRenderer()
	: m_shaderProgram(
		std::filesystem::path(SOURCE_DIR) / "shaders/ring.vert",
		std::filesystem::path(SOURCE_DIR) / "shaders/ring.frag")
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void SceneRenderer::Render(const int framebufferWidth, const int framebufferHeight) const
{
	if (framebufferWidth <= 0 || framebufferHeight <= 0)
	{
		return;
	}

	glClear(GL_COLOR_BUFFER_BIT);

	SetViewport(framebufferWidth, framebufferHeight);

	m_shaderProgram.Use();

	DrawRectangle();
}

void SceneRenderer::SetViewport(const int framebufferWidth, const int framebufferHeight)
{
	int imageHeight = framebufferHeight;
	int imageWidth = imageHeight * 2;

	if (imageWidth > framebufferWidth)
	{
		imageWidth = framebufferWidth - framebufferWidth % 2;
		imageHeight = imageWidth / 2;
	}

	const int viewportX = (framebufferWidth - imageWidth) / 2;
	const int viewportY = (framebufferHeight - imageHeight) / 2;

	glViewport(viewportX, viewportY, imageWidth, imageHeight);
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
