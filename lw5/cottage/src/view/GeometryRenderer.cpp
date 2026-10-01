#include "view/GeometryRenderer.h"

#include <GL/glew.h>

#include <array>
#include <cmath>

namespace
{
struct TexturedVertex
{
	float x;
	float y;
	float z;
	float u;
	float v;
};

void DrawVertex(const TexturedVertex& vertex)
{
	glTexCoord2f(vertex.u, vertex.v);
	glVertex3f(vertex.x, vertex.y, vertex.z);
}

void DrawQuad(const Vector3& normal, const std::array<TexturedVertex, 4>& vertices)
{
	glBegin(GL_QUADS);
	glNormal3f(normal.x, normal.y, normal.z);
	for (const TexturedVertex& vertex : vertices)
	{
		DrawVertex(vertex);
	}
	glEnd();
}
} // namespace

void GeometryRenderer::Draw(const GeometryDescription& geometry)
{
	switch (geometry.type)
	{
	case GeometryType::Box:
		DrawBox(geometry);
		break;
	case GeometryType::Ground:
		DrawGround(geometry);
		break;
	case GeometryType::Roof:
		DrawRoof(geometry);
		break;
	}
}

void GeometryRenderer::DrawBox(const GeometryDescription& geometry)
{
	const float halfWidth = geometry.width / 2.0f;
	const float halfDepth = geometry.depth / 2.0f;
	const float repeatX = geometry.width / geometry.textureScale;
	const float repeatY = geometry.depth / geometry.textureScale;
	const float repeatZ = geometry.height / geometry.textureScale;
	const float top = geometry.height;

	DrawQuad({ 0.0f, 1.0f, 0.0f }, { { { halfWidth, halfDepth, 0.0f, 0.0f, 0.0f }, { -halfWidth, halfDepth, 0.0f, repeatX, 0.0f }, { -halfWidth, halfDepth, top, repeatX, repeatZ }, { halfWidth, halfDepth, top, 0.0f, repeatZ } } });
	DrawQuad({ 0.0f, -1.0f, 0.0f }, { { { -halfWidth, -halfDepth, 0.0f, 0.0f, 0.0f }, { halfWidth, -halfDepth, 0.0f, repeatX, 0.0f }, { halfWidth, -halfDepth, top, repeatX, repeatZ }, { -halfWidth, -halfDepth, top, 0.0f, repeatZ } } });
	DrawQuad({ 1.0f, 0.0f, 0.0f }, { { { halfWidth, -halfDepth, 0.0f, 0.0f, 0.0f }, { halfWidth, halfDepth, 0.0f, repeatY, 0.0f }, { halfWidth, halfDepth, top, repeatY, repeatZ }, { halfWidth, -halfDepth, top, 0.0f, repeatZ } } });
	DrawQuad({ -1.0f, 0.0f, 0.0f }, { { { -halfWidth, halfDepth, 0.0f, 0.0f, 0.0f }, { -halfWidth, -halfDepth, 0.0f, repeatY, 0.0f }, { -halfWidth, -halfDepth, top, repeatY, repeatZ }, { -halfWidth, halfDepth, top, 0.0f, repeatZ } } });
	DrawQuad({ 0.0f, 0.0f, 1.0f }, { { { -halfWidth, -halfDepth, top, 0.0f, 0.0f }, { halfWidth, -halfDepth, top, repeatX, 0.0f }, { halfWidth, halfDepth, top, repeatX, repeatY }, { -halfWidth, halfDepth, top, 0.0f, repeatY } } });
	DrawQuad({ 0.0f, 0.0f, -1.0f }, { { { -halfWidth, halfDepth, 0.0f, 0.0f, 0.0f }, { halfWidth, halfDepth, 0.0f, repeatX, 0.0f }, { halfWidth, -halfDepth, 0.0f, repeatX, repeatY }, { -halfWidth, -halfDepth, 0.0f, 0.0f, repeatY } } });
}

void GeometryRenderer::DrawGround(const GeometryDescription& geometry)
{
	const float halfWidth = geometry.width / 2.0f;
	const float halfDepth = geometry.depth / 2.0f;
	const float repeatX = geometry.width / geometry.textureScale;
	const float repeatY = geometry.depth / geometry.textureScale;
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-halfWidth, -halfDepth, 0.0f);
	glTexCoord2f(repeatX, 0.0f);
	glVertex3f(halfWidth, -halfDepth, 0.0f);
	glTexCoord2f(repeatX, repeatY);
	glVertex3f(halfWidth, halfDepth, 0.0f);
	glTexCoord2f(0.0f, repeatY);
	glVertex3f(-halfWidth, halfDepth, 0.0f);
	glEnd();
}

void GeometryRenderer::DrawRoof(const GeometryDescription& geometry)
{
	const float halfWidth = geometry.width / 2.0f;
	const float halfDepth = geometry.depth / 2.0f;
	const float repeatY = geometry.depth / geometry.textureScale;
	const float repeatZ = geometry.height / geometry.textureScale;
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(halfWidth, halfDepth, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-halfWidth, halfDepth, 0.0f);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0f, halfDepth, geometry.height);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-halfWidth, -halfDepth, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(halfWidth, -halfDepth, 0.0f);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0f, -halfDepth, geometry.height);
	glEnd();
	glBegin(GL_QUADS);
	const float slopeLength = std::sqrt(halfWidth * halfWidth + geometry.height * geometry.height);
	const float normalX = geometry.height / slopeLength;
	const float normalZ = halfWidth / slopeLength;
	glNormal3f(-normalX, 0.0f, normalZ);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-halfWidth, -halfDepth, 0.0f);
	glTexCoord2f(0.0f, repeatZ);
	glVertex3f(0.0f, -halfDepth, geometry.height);
	glTexCoord2f(repeatY, repeatZ);
	glVertex3f(0.0f, halfDepth, geometry.height);
	glTexCoord2f(repeatY, 0.0f);
	glVertex3f(-halfWidth, halfDepth, 0.0f);
	glNormal3f(normalX, 0.0f, normalZ);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, -halfDepth, geometry.height);
	glTexCoord2f(0.0f, repeatZ);
	glVertex3f(halfWidth, -halfDepth, 0.0f);
	glTexCoord2f(repeatY, repeatZ);
	glVertex3f(halfWidth, halfDepth, 0.0f);
	glTexCoord2f(repeatY, 0.0f);
	glVertex3f(0.0f, halfDepth, geometry.height);
	glEnd();
}
