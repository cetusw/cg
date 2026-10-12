#include "view/GlowRenderer.h"

#include "view/SceneRenderer.h"

#include <filesystem>

GlowRenderer::GlowRenderer(const int width, const int height)
	: m_glowFramebuffer(width, height, true)
	, m_gaussianBlur(width, height)
	, m_lightMotionBlur(width, height)
	, m_compositeProgram(
		std::filesystem::path(SOURCE_DIR) / "shaders/fullscreen.vert",
		std::filesystem::path(SOURCE_DIR) / "shaders/composite.frag")
	, m_width(width)
	, m_height(height)
{
}

void GlowRenderer::Resize(const int width, const int height)
{
	if (width <= 0 || height <= 0)
	{
		return;
	}

	m_width = width;
	m_height = height;
	m_glowFramebuffer.Resize(width, height);
	m_gaussianBlur.Resize(width, height);
	m_lightMotionBlur.Resize(width, height);
}

void GlowRenderer::ResetLightMotionBlur()
{
	m_lightMotionBlur.Reset();
}

void GlowRenderer::SetLightMotionBlurEnabled(const bool isEnabled)
{
	if (isEnabled && !m_isLightMotionBlurEnabled)
	{
		m_lightMotionBlur.Reset();
	}

	m_isLightMotionBlurEnabled = isEnabled;
}

void GlowRenderer::Render(const Scene& scene, SceneRenderer& sceneRenderer, const float deltaTime)
{
	m_glowFramebuffer.Bind();
	sceneRenderer.RenderGlowMap(scene);

	const Texture2D& blurredTexture =
		m_gaussianBlur.Apply(m_glowFramebuffer.GetColorTexture());

	const Texture2D* resultTexture = &blurredTexture;

	if (m_isLightMotionBlurEnabled)
	{
		resultTexture = &m_lightMotionBlur.Apply(blurredTexture, deltaTime);
	}

	Framebuffer::BindDefault();
	glViewport(0, 0, m_width, m_height);

	Composite(*resultTexture);
}

void GlowRenderer::Composite(const Texture2D& resultedTexture)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	m_compositeProgram.Use();

	glActiveTexture(GL_TEXTURE0);
	resultedTexture.Bind();
	m_compositeProgram.SetIntUniform("image", 0);

	DrawFullscreenQuad();

	glUseProgram(0);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void GlowRenderer::DrawFullscreenQuad()
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
