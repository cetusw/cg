#pragma once

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
};
