#pragma once

#include "view/ShaderProgram.h"

class SceneRenderer
{
public:
	SceneRenderer();

	void Render(int framebufferWidth, int framebufferHeight) const;

private:
	static void SetViewport(int framebufferWidth, int framebufferHeight);

	static void DrawRectangle();

	ShaderProgram m_shaderProgram;
};
