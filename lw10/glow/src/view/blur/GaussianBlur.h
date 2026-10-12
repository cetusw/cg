#pragma once

#include "view/Framebuffer.h"
#include "view/ShaderProgram.h"

class GaussianBlur
{
public:
	GaussianBlur(int width, int height);

	void Resize(int width, int height);
	[[nodiscard]] const Texture2D& Apply(const Texture2D& inputTexture);

private:
	void Blur(const Texture2D& inputTexture, const Framebuffer& output, float horizontalOffset, float verticalOffset);
	static void DrawFullscreenQuad();

	Framebuffer m_horizontalFramebuffer;
	Framebuffer m_verticalFramebuffer;
	ShaderProgram m_shaderProgram;
	int m_width{};
	int m_height{};
};
