#pragma once

#include "model/types/Camera.h"
#include "view/ShaderProgram.h"

class SceneRenderer
{
public:
	SceneRenderer();

	static void Initialize();
	void Render(const Camera& camera) const;
	static void SetProjection(int width, int height);

private:
	static void PrepareFrame();
	static void ConfigureCamera(const Camera& camera);

	ShaderProgram m_shaderProgram;
};
