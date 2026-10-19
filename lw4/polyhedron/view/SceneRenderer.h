#pragma once

#include "model/Scene.h"

class SceneRenderer
{
public:
	static void Initialize();
	static void SetProjection(int width, int height);
	static void Render(const Scene& scene);

private:
	static void ApplyMainLight(const PointLight& light);
	static void ApplyMaterial(const MaterialDescription& material);
};
