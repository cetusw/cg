#pragma once

#include "../types/Material.h"

namespace Materials
{
inline constexpr MaterialDescription Ground{
	{ 0.0f, 0.5f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f },
	4.0f
};

inline constexpr MaterialDescription Concrete{
	{ 0.6f, 0.6f, 0.7f },
	{ 0.65f, 0.65f, 0.8f },
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

inline constexpr MaterialDescription Fence{
	{ 0.18f, 0.10f, 0.04f },
	{ 0.45f, 0.25f, 0.10f },
	{ 0.03f, 0.03f, 0.03f },
	4.0f
};
} // namespace Materials
