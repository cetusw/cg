#pragma once

#include "view/Texture2D.h"

#include <GL/glew.h>

class Framebuffer
{
public:
	Framebuffer(int width, int height, bool hasDepthBuffer);
	~Framebuffer();

	Framebuffer(const Framebuffer&) = delete;
	Framebuffer& operator=(const Framebuffer&) = delete;
	Framebuffer(Framebuffer&&) = delete;
	Framebuffer& operator=(Framebuffer&&) = delete;

	void Bind() const;
	void Resize(int width, int height) const;
	[[nodiscard]] const Texture2D& GetColorTexture() const;

	static void BindDefault();

private:
	void CreateDepthBuffer(int width, int height);
	static void CheckCompleteness();
	void Release() noexcept;

	GLuint m_id{};
	Texture2D m_colorTexture;
	GLuint m_depthBuffer{};
	bool m_hasDepthBuffer = false;
};
