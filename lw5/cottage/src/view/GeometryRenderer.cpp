#include "view/GeometryRenderer.h"

#include <GL/glew.h>

#include <array>

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

// TODO выучить математику

namespace
{
struct TexturedVertex
{
	TexturedVertex(
		const glm::vec3& position,
		const float u,
		const float v)
		: position(position)
		, u(u)
		, v(v)
	{
	}

	glm::vec3 position;
	float u{};
	float v{};
};

struct BoxVertices
{
	BoxVertices(
		const float halfWidth,
		const float halfDepth,
		const float bottom,
		const float top)
		: leftBackBottom(-halfWidth, -halfDepth, bottom)
		, rightBackBottom(halfWidth, -halfDepth, bottom)
		, leftFrontBottom(-halfWidth, halfDepth, bottom)
		, rightFrontBottom(halfWidth, halfDepth, bottom)
		, leftBackTop(-halfWidth, -halfDepth, top)
		, rightBackTop(halfWidth, -halfDepth, top)
		, leftFrontTop(-halfWidth, halfDepth, top)
		, rightFrontTop(halfWidth, halfDepth, top)
	{
	}

	glm::vec3 leftBackBottom;
	glm::vec3 rightBackBottom;
	glm::vec3 leftFrontBottom;
	glm::vec3 rightFrontBottom;
	glm::vec3 leftBackTop;
	glm::vec3 rightBackTop;
	glm::vec3 leftFrontTop;
	glm::vec3 rightFrontTop;
};

struct PlaneVertices
{
	PlaneVertices(
		const float halfWidth,
		const float halfDepth,
		const float height)
		: leftBack(-halfWidth, -halfDepth, height)
		, rightBack(halfWidth, -halfDepth, height)
		, leftFront(-halfWidth, halfDepth, height)
		, rightFront(halfWidth, halfDepth, height)
	{
	}

	glm::vec3 leftBack;
	glm::vec3 rightBack;
	glm::vec3 leftFront;
	glm::vec3 rightFront;
};

struct TriangularPrismVertices
{
	TriangularPrismVertices(
		const float halfWidth,
		const float halfDepth,
		const float bottom,
		const float top)
		: leftBack(-halfWidth, -halfDepth, bottom)
		, rightBack(halfWidth, -halfDepth, bottom)
		, topBack(0.0f, -halfDepth, top)
		, leftFront(-halfWidth, halfDepth, bottom)
		, rightFront(halfWidth, halfDepth, bottom)
		, topFront(0.0f, halfDepth, top)
	{
	}

	glm::vec3 leftBack;
	glm::vec3 rightBack;
	glm::vec3 topBack;
	glm::vec3 leftFront;
	glm::vec3 rightFront;
	glm::vec3 topFront;
};

struct TextureRepeat
{
	explicit TextureRepeat(const GeometryDescription& geometry)
		: m_textureScale(geometry.textureScale)
	{
	}

	[[nodiscard]] float Between(
		const glm::vec3& first,
		const glm::vec3& second) const
	{
		return glm::length(second - first) / m_textureScale;
	}

private:
	float m_textureScale;
};

void DrawVertex(const TexturedVertex& vertex)
{
	glTexCoord2f(vertex.u, vertex.v);
	glVertex3f(
		vertex.position.x,
		vertex.position.y,
		vertex.position.z);
}

void DrawQuad(
	const glm::vec3& normal,
	const std::array<TexturedVertex, 4>& vertices)
{
	glBegin(GL_QUADS);
	glNormal3f(normal.x, normal.y, normal.z);

	for (const TexturedVertex& vertex : vertices)
	{
		DrawVertex(vertex);
	}

	glEnd();
}

void DrawTriangle(
	const glm::vec3& normal,
	const std::array<TexturedVertex, 3>& vertices)
{
	glBegin(GL_TRIANGLES);
	glNormal3f(normal.x, normal.y, normal.z);

	for (const TexturedVertex& vertex : vertices)
	{
		DrawVertex(vertex);
	}

	glEnd();
}

glm::vec3 CalculateNormal(
	const glm::vec3& first,
	const glm::vec3& second,
	const glm::vec3& third)
{
	return glm::normalize(
		glm::cross(second - first, third - first));
}
} // namespace

void GeometryRenderer::Draw(const GeometryDescription& geometry)
{
	switch (geometry.type)
	{
	case GeometryType::Box:
		DrawBox(geometry);
		break;

	case GeometryType::Plane:
		DrawPlane(geometry);
		break;

	case GeometryType::TriangularPrism:
		DrawTriangularPrism(geometry);
		break;
	}
}

void GeometryRenderer::DrawBox(const GeometryDescription& geometry)
{
	const float halfWidth = geometry.width / 2.0f;
	const float halfDepth = geometry.depth / 2.0f;
	constexpr float bottom = 0.0f;
	const float top = geometry.height;

	const TextureRepeat repeat(geometry);
	const BoxVertices vertices(
		halfWidth,
		halfDepth,
		bottom,
		top);
	const float repeatX = repeat.Between(
		vertices.leftBackBottom,
		vertices.rightBackBottom);
	const float repeatY = repeat.Between(
		vertices.leftBackBottom,
		vertices.leftFrontBottom);
	const float repeatZ = repeat.Between(
		vertices.leftBackBottom,
		vertices.leftBackTop);

	DrawQuad(
		{ 0.0f, 1.0f, 0.0f },
		{ TexturedVertex(vertices.rightFrontBottom, 0.0f, 0.0f),
			TexturedVertex(vertices.leftFrontBottom, repeatX, 0.0f),
			TexturedVertex(vertices.leftFrontTop, repeatX, repeatZ),
			TexturedVertex(vertices.rightFrontTop, 0.0f, repeatZ) });

	DrawQuad(
		{ 0.0f, -1.0f, 0.0f },
		{ TexturedVertex(vertices.leftBackBottom, 0.0f, 0.0f),
			TexturedVertex(vertices.rightBackBottom, repeatX, 0.0f),
			TexturedVertex(vertices.rightBackTop, repeatX, repeatZ),
			TexturedVertex(vertices.leftBackTop, 0.0f, repeatZ) });

	DrawQuad(
		{ 1.0f, 0.0f, 0.0f },
		{ TexturedVertex(vertices.rightBackBottom, 0.0f, 0.0f),
			TexturedVertex(vertices.rightFrontBottom, repeatY, 0.0f),
			TexturedVertex(vertices.rightFrontTop, repeatY, repeatZ),
			TexturedVertex(vertices.rightBackTop, 0.0f, repeatZ) });

	DrawQuad(
		{ -1.0f, 0.0f, 0.0f },
		{ TexturedVertex(vertices.leftFrontBottom, 0.0f, 0.0f),
			TexturedVertex(vertices.leftBackBottom, repeatY, 0.0f),
			TexturedVertex(vertices.leftBackTop, repeatY, repeatZ),
			TexturedVertex(vertices.leftFrontTop, 0.0f, repeatZ) });

	DrawQuad(
		{ 0.0f, 0.0f, 1.0f },
		{ TexturedVertex(vertices.leftBackTop, 0.0f, 0.0f),
			TexturedVertex(vertices.rightBackTop, repeatX, 0.0f),
			TexturedVertex(vertices.rightFrontTop, repeatX, repeatY),
			TexturedVertex(vertices.leftFrontTop, 0.0f, repeatY) });

	DrawQuad(
		{ 0.0f, 0.0f, -1.0f },
		{ TexturedVertex(vertices.leftFrontBottom, 0.0f, 0.0f),
			TexturedVertex(vertices.rightFrontBottom, repeatX, 0.0f),
			TexturedVertex(vertices.rightBackBottom, repeatX, repeatY),
			TexturedVertex(vertices.leftBackBottom, 0.0f, repeatY) });
}

void GeometryRenderer::DrawPlane(const GeometryDescription& geometry)
{
	const float halfWidth = geometry.width / 2.0f;
	const float halfDepth = geometry.depth / 2.0f;
	constexpr float height = 0.0f;

	const TextureRepeat repeat(geometry);
	const PlaneVertices vertices(
		halfWidth,
		halfDepth,
		height);
	const float repeatX = repeat.Between(
		vertices.leftBack,
		vertices.rightBack);
	const float repeatY = repeat.Between(
		vertices.leftBack,
		vertices.leftFront);

	DrawQuad(
		{ 0.0f, 0.0f, 1.0f },
		{ TexturedVertex(vertices.leftBack, 0.0f, 0.0f),
			TexturedVertex(vertices.rightBack, repeatX, 0.0f),
			TexturedVertex(vertices.rightFront, repeatX, repeatY),
			TexturedVertex(vertices.leftFront, 0.0f, repeatY) });
}

void GeometryRenderer::DrawTriangularPrism(
	const GeometryDescription& geometry)
{
	const float halfWidth = geometry.width / 2.0f;
	const float halfDepth = geometry.depth / 2.0f;
	constexpr float bottom = 0.0f;
	const float top = geometry.height;

	const TextureRepeat repeat(geometry);
	const TriangularPrismVertices vertices(
		halfWidth,
		halfDepth,
		bottom,
		top);
	const float repeatX = repeat.Between(
		vertices.leftBack,
		vertices.rightBack);
	const float repeatY = repeat.Between(
		vertices.leftBack,
		vertices.leftFront);
	const float repeatZ = geometry.height / geometry.textureScale;
	const float slopeRepeat = repeat.Between(
		vertices.leftBack,
		vertices.topBack);

	DrawTriangle(
		{ 0.0f, 1.0f, 0.0f },
		{ TexturedVertex(vertices.leftFront, 0.0f, 0.0f),
			TexturedVertex(vertices.topFront, repeatX / 2.0f, repeatZ),
			TexturedVertex(vertices.rightFront, repeatX, 0.0f) });

	DrawTriangle(
		{ 0.0f, -1.0f, 0.0f },
		{ TexturedVertex(vertices.leftBack, 0.0f, 0.0f),
			TexturedVertex(vertices.rightBack, 1.0f, 0.0f),
			TexturedVertex(vertices.topBack, 0.5f, 1.0f) });

	DrawQuad(
		CalculateNormal(
			vertices.leftBack,
			vertices.topBack,
			vertices.topFront),
		{ TexturedVertex(vertices.leftBack, 0.0f, 0.0f),
			TexturedVertex(vertices.topBack, 0.0f, slopeRepeat),
			TexturedVertex(vertices.topFront, repeatY, slopeRepeat),
			TexturedVertex(vertices.leftFront, repeatY, 0.0f) });

	DrawQuad(
		CalculateNormal(
			vertices.topBack,
			vertices.rightBack,
			vertices.rightFront),
		{ TexturedVertex(vertices.topBack, 0.0f, 0.0f),
			TexturedVertex(vertices.rightBack, 0.0f, slopeRepeat),
			TexturedVertex(vertices.rightFront, repeatY, slopeRepeat),
			TexturedVertex(vertices.topFront, repeatY, 0.0f) });

	DrawQuad(
		{ 0.0f, 0.0f, -1.0f },
		{ TexturedVertex(vertices.leftFront, 0.0f, 0.0f),
			TexturedVertex(vertices.rightFront, repeatX, 0.0f),
			TexturedVertex(vertices.rightBack, repeatX, repeatY),
			TexturedVertex(vertices.leftBack, 0.0f, repeatY) });
}
