#pragma once

enum class GeometryType
{
	Box,
	TriangularPrism,
	Plane
};

struct GeometryDescription
{
	GeometryType type{};
	float width{};
	float depth{};
	float height{};
	float textureScale = 1.0f;
};
