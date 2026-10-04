#pragma once

struct RgbColor
{
	float red{};
	float green{};
	float blue{};
};

struct MaterialDescription
{
	RgbColor ambient; // TODO подумать над тем, чтобы вынести параметры в отдельных объект
	RgbColor diffuse;
	RgbColor specular;
	float shininess{};
	float opacity = 1.0f;
};
