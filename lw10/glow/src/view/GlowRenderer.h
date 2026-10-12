#pragma once

#include "blur/GaussianBlur.h"
#include "blur/LightMotionBlur.h"
#include "view/Framebuffer.h"
#include "view/ShaderProgram.h"

class Scene;
class SceneRenderer;

class GlowRenderer
{
public:
	GlowRenderer(int width, int height);

	void Resize(int width, int height);
	void ResetLightMotionBlur();
	void SetLightMotionBlurEnabled(bool isEnabled);
	void Render(const Scene& scene, SceneRenderer& sceneRenderer, float deltaTime);

private:
	void Composite(const Texture2D& resultedTexture);
	static void DrawFullscreenQuad();

	Framebuffer m_glowFramebuffer;
	GaussianBlur m_gaussianBlur;
	LightMotionBlur m_lightMotionBlur;
	ShaderProgram m_compositeProgram;
	int m_width{};
	int m_height{};
	bool m_isLightMotionBlurEnabled = true;
};
