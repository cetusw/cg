#pragma once

#include "Texture2D.h"
#include "view/ShaderProgram.h"

class SceneRenderer
{
public:
	SceneRenderer();

	void Render(float time);

private:
	static void PrepareFrame();
	static void DrawRectangle();

	ShaderProgram m_shaderProgram;
	Texture2D m_texture;
};
