#pragma once

#include <glm/vec3.hpp>

namespace CottageDimensions
{
inline constexpr float GarageOffsetX = 5.0f;
inline constexpr float GarageOffsetY = 0.0f;
inline constexpr float GarageOffsetZ = 0.0f;
inline constexpr glm::vec3 GarageOffset{
	GarageOffsetX,
	GarageOffsetY,
	GarageOffsetZ
};

inline constexpr float PorchOffsetX = 1.5f;
inline constexpr float PorchOffsetY = 3.0f;
inline constexpr float PorchOffsetZ = 0.0f;
inline constexpr glm::vec3 PorchOffset{
	PorchOffsetX,
	PorchOffsetY,
	PorchOffsetZ
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
inline constexpr glm::vec3 ColumnOffset{
	1.0f,
	0.5f,
	0.0f
};
} // namespace PorchDimensions

namespace FenceDimensions
{
inline constexpr float SectionLength = 2.0f;
inline constexpr int WidthSectionCount = 8;
inline constexpr int DepthSectionCount = 6;
inline constexpr float HalfWidth = WidthSectionCount * SectionLength / 2.0f;
inline constexpr float HalfDepth = DepthSectionCount * SectionLength / 2.0f;

inline constexpr float PanelHeight = 1.1f;
inline constexpr float PanelThickness = 0.15f;
inline constexpr float PostSize = 0.2f;
inline constexpr float PostHeight = 1.3f;

// Front sections are counted from the right corner towards the left corner.
inline constexpr int DrivewayGapStartSection = 0;
inline constexpr int DrivewayGapSectionCount = 2;
inline constexpr int EntranceGapStartSection = 3;
inline constexpr int EntranceGapSectionCount = 1;
} // namespace FenceDimensions

namespace GarageDimensions
{
inline constexpr float BodyWidth = 4.0f;
inline constexpr float BodyDepth = 4.0f;
inline constexpr float BodyHeight = 2.0f;

inline constexpr float DoorWidth = 2.0f;
inline constexpr float DoorHeight = 2.0f;
inline constexpr float DoorThickness = 0.10f;

inline constexpr float WindowThickness = 0.10f;
inline constexpr float WindowWidth = 2.0f;
inline constexpr float WindowHeight = 1.0f;
inline constexpr float WindowBaseHeight = 0.5f;
} // namespace GarageDimensions
