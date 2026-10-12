#include "view/blur/GaussianBlur.h"

#include <algorithm>
#include <filesystem>

namespace
{
int GetBlurSize(const int size)
{
	return std::max(1, size / 2);
}
} // namespace

GaussianBlur::GaussianBlur(const int width, const int height)
	: m_horizontalFramebuffer(GetBlurSize(width), GetBlurSize(height), false)
	, m_verticalFramebuffer(GetBlurSize(width), GetBlurSize(height), false)
	, m_shaderProgram(
		std::filesystem::path(SOURCE_DIR) / "shaders/fullscreen.vert",
		std::filesystem::path(SOURCE_DIR) / "shaders/gaussian-blur.frag")
{
	Resize(width, height);
}

void GaussianBlur::Resize(const int width, const int height)
{
	m_width = GetBlurSize(width);
	m_height = GetBlurSize(height);
	m_horizontalFramebuffer.Resize(m_width, m_height);
	m_verticalFramebuffer.Resize(m_width, m_height);
}

const Texture2D& GaussianBlur::Apply(const Texture2D& inputTexture)
{
	Blur(inputTexture, m_horizontalFramebuffer, 1.0f / m_width, 0.0f);
	Blur(m_horizontalFramebuffer.GetColorTexture(), m_verticalFramebuffer, 0.0f, 1.0f / m_height);
	Blur(m_verticalFramebuffer.GetColorTexture(), m_horizontalFramebuffer, 1.0f / m_width, 0.0f);
	Blur(m_horizontalFramebuffer.GetColorTexture(), m_verticalFramebuffer, 0.0f, 1.0f / m_height);
	return m_verticalFramebuffer.GetColorTexture();
}

void GaussianBlur::Blur(
	const Texture2D& inputTexture,
	const Framebuffer& output,
	const float horizontalOffset,
	const float verticalOffset)
{
	output.Bind();
	glViewport(0, 0, m_width, m_height);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	m_shaderProgram.Use();

	inputTexture.Bind();
	glActiveTexture(GL_TEXTURE0);
	m_shaderProgram.SetIntUniform("image", 0);

	m_shaderProgram.SetVec2Uniform("texelOffset", { horizontalOffset, verticalOffset });

	DrawFullscreenQuad();

	glUseProgram(0);
}

void GaussianBlur::DrawFullscreenQuad()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

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

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
