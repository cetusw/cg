#pragma once

#include "model/Scene.h"

class GeometryRenderer
{
public:
	static void Draw(const GeometryDescription& geometry);

private:
	static void DrawBox(const GeometryDescription& geometry);
	static void DrawPlane(const GeometryDescription& geometry);
	static void DrawTriangularPrism(const GeometryDescription& geometry);
};
