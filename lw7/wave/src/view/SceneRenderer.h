#pragma once

#include "Texture2D.h"
#include "view/ShaderProgram.h"

class SceneRenderer
{
public:
	SceneRenderer();

	void Render(glm::vec2 center, float elapsedTime, bool isWaveActive, float aspectRatio);
	void SwapTextures();

private:
	static void PrepareFrame();
	static void DrawRectangle();

	ShaderProgram m_shaderProgram;
	Texture2D m_textureFrom;
	Texture2D m_textureTo;
};
