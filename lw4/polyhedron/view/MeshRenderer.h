#pragma once

#include "model/Mesh.h"

class MeshRenderer
{
public:
	static void Draw(const Mesh& mesh);

private:
	static void DrawFaces(const Mesh& mesh, float alpha);
	static void DrawEdges(const Mesh& mesh);
};
