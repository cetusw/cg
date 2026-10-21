#pragma once

#include "Texture2D.h"
#include "view/ShaderProgram.h"

class SceneRenderer
{
public:
	SceneRenderer();

	void Render(glm::vec2 center, float elapsedTime, bool isWaveActive, int framebufferWidth, int framebufferHeight);
	[[nodiscard]] bool TryGetTextureCoordinates(
		glm::dvec2 framebufferPosition,
		int framebufferWidth,
		int framebufferHeight,
		glm::vec2& textureCoordinates) const;
	void SwapTextures();

private:
	struct Viewport
	{
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
	};

	static void PrepareFrame();
	[[nodiscard]] Viewport CalculateViewport(int framebufferWidth, int framebufferHeight) const;
	static void DrawRectangle();

	ShaderProgram m_shaderProgram;
	Texture2D m_textureFrom;
	Texture2D m_textureTo;
};
