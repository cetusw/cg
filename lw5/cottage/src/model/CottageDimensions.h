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

inline constexpr float WindowWidth = 1.0f;
inline constexpr float WindowHeight = 1.0f;
inline constexpr float WindowThickness = 0.10f;
inline constexpr float WindowBaseHeight = 0.75f;

inline constexpr float DoorWidth = 1.0f;
inline constexpr float DoorHeight = 1.5f;
inline constexpr float DoorThickness = 0.10f;
inline constexpr float DoorBaseHeight = 0.5f;
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

namespace FenceDimensions
{
inline constexpr float HalfWidth = 8.0f;
inline constexpr float HalfDepth = 6.0f;
inline constexpr float Height = 1.2f;
inline constexpr float PostSize = 0.2f;
inline constexpr float RailThickness = 0.12f;
inline constexpr float LowerRailHeight = 0.35f;
inline constexpr float UpperRailHeight = 0.85f;

inline constexpr float GateWidth = 2.4f;
inline constexpr float GateCenterX = CottageDimensions::PorchOffset.x;
inline constexpr float GateLeftX = GateCenterX - GateWidth / 2.0f;
inline constexpr float GateRightX = GateCenterX + GateWidth / 2.0f;
inline constexpr float FrontLeftRailWidth = GateLeftX + HalfWidth;
inline constexpr float FrontRightRailWidth = HalfWidth - GateRightX;
inline constexpr float FrontLeftRailCenterX = (GateLeftX - HalfWidth) / 2.0f;
inline constexpr float FrontRightRailCenterX = (GateRightX + HalfWidth) / 2.0f;
} // namespace FenceDimensions
