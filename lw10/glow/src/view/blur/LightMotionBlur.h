#pragma once

#include "view/Framebuffer.h"
#include "view/ShaderProgram.h"

class LightMotionBlur
{
public:
	LightMotionBlur(int width, int height);

	LightMotionBlur(const LightMotionBlur&) = delete;
	LightMotionBlur& operator=(const LightMotionBlur&) = delete;
	LightMotionBlur(LightMotionBlur&&) = delete;
	LightMotionBlur& operator=(LightMotionBlur&&) = delete;

	void Resize(int width, int height);
	void Reset();
	[[nodiscard]] const Texture2D& Apply(const Texture2D& inputTexture, float deltaTime);

private:
	[[nodiscard]] const Framebuffer& GetPreviousFramebuffer() const;
	[[nodiscard]] Framebuffer& GetOutputFramebuffer();
	static void DrawFullscreenQuad();

	Framebuffer m_firstFramebuffer;
	Framebuffer m_secondFramebuffer;
	ShaderProgram m_shaderProgram;
	int m_width{};
	int m_height{};
	bool m_isFirstFramebufferPrevious = true;
};
