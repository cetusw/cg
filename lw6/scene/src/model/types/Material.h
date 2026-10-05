#pragma once

struct RgbColor
{
	float red{};
	float green{};
	float blue{};
};

struct MaterialDescription
{
	RgbColor ambient;
	RgbColor diffuse;
	RgbColor specular;
	float shininess{};
	float opacity = 1.0f;
};
