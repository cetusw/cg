#pragma once

#include "model/Scene.h"

namespace Materials
{
inline constexpr MaterialDescription Ground{
	{ 0.10f, 0.20f, 0.10f },
	{ 0.35f, 0.65f, 0.30f },
	{ 0.05f, 0.05f, 0.05f },
	4.0f
};

inline constexpr MaterialDescription Wall{
	{ 0.30f, 0.10f, 0.08f },
	{ 0.75f, 0.25f, 0.15f },
	{ 0.10f, 0.10f, 0.10f },
	8.0f
};

inline constexpr MaterialDescription Roof{
	{ 0.15f, 0.15f, 0.15f },
	{ 0.60f, 0.60f, 0.60f },
	{ 0.15f, 0.15f, 0.15f },
	12.0f
};

inline constexpr MaterialDescription Foundation{
	{ 0.15f, 0.15f, 0.15f },
	{ 0.50f, 0.50f, 0.50f },
	{ 0.10f, 0.10f, 0.10f },
	4.0f
};

inline constexpr MaterialDescription Window{
	{ 0.10f, 0.15f, 0.20f },
	{ 0.25f, 0.45f, 0.65f },
	{ 0.80f, 0.80f, 0.80f },
	64.0f
};

inline constexpr MaterialDescription Door{
	{ 0.18f, 0.08f, 0.03f },
	{ 0.45f, 0.20f, 0.08f },
	{ 0.10f, 0.10f, 0.10f },
	8.0f
};
} // namespace Materials
