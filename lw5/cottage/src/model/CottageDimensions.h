#pragma once

#include "model/Scene.h"

namespace CottageDimensions
{
inline constexpr Vector3 GarageOffset{
	5.0f,
	0.0f,
	0.0f
};

inline constexpr Vector3 PorchOffset{
	1.5f,
	3.0f,
	0.0f
};
} // namespace CottageDimensions

namespace HouseDimensions
{
inline constexpr float WallHeight = 2.0f;

inline constexpr float FirstBodyWidth = 3.0f;
inline constexpr float FirstBodyDepth = 4.0f;
inline constexpr float SecondBodyWidth = 3.0f;
inline constexpr float SecondBodyDepth = 6.0f;
inline constexpr float BodyOffsetX = 1.5f;
inline constexpr float SecondBodyOffsetY = 1.0f;

inline constexpr float FirstRoofWidth = 6.0f;
inline constexpr float FirstRoofDepth = 10.0f;
inline constexpr float FirstRoofHeight = 1.5f;
inline constexpr float FirstRoofOffsetX = 2.0f;
inline constexpr float FirstRoofRotationZ = 90.0f;

inline constexpr float SecondRoofWidth = 6.0f;
inline constexpr float SecondRoofDepth = 4.0f;
inline constexpr float SecondRoofHeight = 1.0f;
inline constexpr float SecondRoofOffsetY = 2.0f;
inline constexpr float RoofBaseHeight = WallHeight;
} // namespace HouseDimensions

namespace PorchDimensions
{
inline constexpr float PlatformWidth = 3.0f;
inline constexpr float PlatformDepth = 2.0f;
inline constexpr float PlatformHeight = 0.5f;

inline constexpr float ColumnWidth = 0.2f;
inline constexpr float ColumnHeight = 2.0f;
inline constexpr Vector3 ColumnOffset{
	1.0f,
	0.5f,
	0.0f
};
} // namespace PorchDimensions
