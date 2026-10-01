#pragma once

#include "model/Scene.h"

class GeometryRenderer
{
public:
	static void Draw(const GeometryDescription& geometry);

private:
	static void DrawBox(const GeometryDescription& geometry);
	static void DrawGround(const GeometryDescription& geometry);
	static void DrawRoof(const GeometryDescription& geometry);
};
