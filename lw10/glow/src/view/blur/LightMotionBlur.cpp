#include "view/blur/LightMotionBlur.h"

#include <algorithm>
#include <filesystem>

namespace
{
int GetMotionBlurSize(const int size)
{
	return std::max(1, size / 2);
}
} // namespace

LightMotionBlur::LightMotionBlur(const int width, const int height)
	: m_firstFramebuffer(GetMotionBlurSize(width), GetMotionBlurSize(height), false)
	, m_secondFramebuffer(GetMotionBlurSize(width), GetMotionBlurSize(height), false)
	, m_shaderProgram(
		  std::filesystem::path(SOURCE_DIR) / "shaders/fullscreen.vert",
		  std::filesystem::path(SOURCE_DIR) / "shaders/light-motion-blur.frag")
{
	Resize(width, height);
}

void LightMotionBlur::Resize(const int width, const int height)
{
	m_width = GetMotionBlurSize(width);
	m_height = GetMotionBlurSize(height);
	m_firstFramebuffer.Resize(m_width, m_height);
	m_secondFramebuffer.Resize(m_width, m_height);
	Reset();
}

void LightMotionBlur::Reset()
{
	GLfloat clearColor[4]{};
	glGetFloatv(GL_COLOR_CLEAR_VALUE, clearColor);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glViewport(0, 0, m_width, m_height);

	m_firstFramebuffer.Bind();
	glClear(GL_COLOR_BUFFER_BIT);

	m_secondFramebuffer.Bind();
	glClear(GL_COLOR_BUFFER_BIT);

	Framebuffer::BindDefault();
	glViewport(0, 0, m_width * 2, m_height * 2);

	glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

	m_isFirstFramebufferPrevious = true;
}

const Texture2D& LightMotionBlur::Apply(
	const Texture2D& inputTexture,
	const float deltaTime)
{
	const Framebuffer& outputFramebuffer = GetOutputFramebuffer();
	outputFramebuffer.Bind();
	glViewport(0, 0, m_width, m_height);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	m_shaderProgram.Use();

	glActiveTexture(GL_TEXTURE0);
	inputTexture.Bind();
	m_shaderProgram.SetIntUniform("currentImage", 0);

	glActiveTexture(GL_TEXTURE1);
	GetPreviousFramebuffer().GetColorTexture().Bind();
	m_shaderProgram.SetIntUniform("previousImage", 1);

	constexpr float DecayRate = 9.75;
	const float previousDecay = std::exp(-DecayRate * deltaTime);
	m_shaderProgram.SetFloatUniform("previousDecay", previousDecay);

	DrawFullscreenQuad();

	glUseProgram(0);

	m_isFirstFramebufferPrevious = !m_isFirstFramebufferPrevious;
	glActiveTexture(GL_TEXTURE0);
	Framebuffer::BindDefault();
	glViewport(0, 0, m_width * 2, m_height * 2);
	return GetPreviousFramebuffer().GetColorTexture();
}

const Framebuffer& LightMotionBlur::GetPreviousFramebuffer() const
{
	return m_isFirstFramebufferPrevious
		? m_firstFramebuffer
		: m_secondFramebuffer;
}

Framebuffer& LightMotionBlur::GetOutputFramebuffer()
{
	return m_isFirstFramebufferPrevious
		? m_secondFramebuffer
		: m_firstFramebuffer;
}

void LightMotionBlur::DrawFullscreenQuad()
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
