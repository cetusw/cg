#include "view/Framebuffer.h"

#include <stdexcept>

Framebuffer::Framebuffer(const int width, const int height, const bool hasDepthBuffer)
	: m_colorTexture(width, height)
	, m_hasDepthBuffer(hasDepthBuffer)
{
	if (GLEW_ARB_framebuffer_object == GL_FALSE)
	{
		throw std::runtime_error("Framebuffer objects are not supported by the OpenGL driver");
	}

	glGenFramebuffers(1, &m_id);
	Bind();
	glFramebufferTexture2D(
		GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D,
		m_colorTexture.GetId(),
		0);

	if (m_hasDepthBuffer)
	{
		CreateDepthBuffer(width, height);
	}

	CheckCompleteness();
	BindDefault();
}

Framebuffer::~Framebuffer()
{
	Release();
}

void Framebuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void Framebuffer::Resize(const int width, const int height) const
{
	Bind();
	m_colorTexture.Resize(width, height);

	if (m_hasDepthBuffer)
	{
		glBindRenderbuffer(
			GL_RENDERBUFFER,
			m_depthBuffer);
		glRenderbufferStorage(
			GL_RENDERBUFFER,
			GL_DEPTH_COMPONENT,
			width,
			height);
	}

	CheckCompleteness();
	BindDefault();
}

const Texture2D& Framebuffer::GetColorTexture() const
{
	return m_colorTexture;
}

void Framebuffer::BindDefault()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::CreateDepthBuffer(const int width, const int height)
{
	glGenRenderbuffers(1, &m_depthBuffer);
	glBindRenderbuffer(
		GL_RENDERBUFFER,
		m_depthBuffer);
	glRenderbufferStorage(
		GL_RENDERBUFFER,
		GL_DEPTH_COMPONENT,
		width,
		height);
	glFramebufferRenderbuffer(
		GL_FRAMEBUFFER,
		GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER,
		m_depthBuffer);
}

void Framebuffer::CheckCompleteness()
{
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		throw std::runtime_error("Failed to create complete framebuffer");
	}
}

void Framebuffer::Release() noexcept
{
	if (m_depthBuffer != 0)
	{
		glDeleteRenderbuffers(1, &m_depthBuffer);
		m_depthBuffer = 0;
	}

	if (m_id != 0)
	{
		glDeleteFramebuffers(1, &m_id);
		m_id = 0;
	}
}
