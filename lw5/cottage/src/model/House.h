#pragma once

#include "types/SceneObject.h"

#include <glm/vec3.hpp>
#include <vector>

class House
{
public:
	explicit House(glm::vec3 position);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;

private:
	static constexpr float WallHeight = 2.0f;

	static constexpr float FirstBodyWidth = 3.0f;
	static constexpr float FirstBodyDepth = 4.0f;
	static constexpr float FirstBodyHalfDepth = FirstBodyDepth / 2.0f;

	static constexpr float SecondBodyWidth = 3.0f;
	static constexpr float SecondBodyDepth = 6.0f;
	static constexpr float SecondBodyHalfWidth = SecondBodyWidth / 2.0f;
	static constexpr float SecondBodyHalfDepth = SecondBodyDepth / 2.0f;
	static constexpr float SideWindowOffsetY = SecondBodyDepth / 4.0f;
	static constexpr float BodyOffsetX = 1.5f;
	static constexpr float SecondBodyOffsetY = 1.0f;

	static constexpr float FirstRoofWidth = FirstBodyDepth;
	static constexpr float FirstRoofDepth = FirstBodyDepth + SecondBodyDepth;
	static constexpr float FirstRoofHeight = 1.5f;
	static constexpr float FirstRoofOffsetX = 2.0f;
	static constexpr float FirstRoofRotationZ = 90.0f;

	static constexpr float FirstRoofShinglesWidth = FirstRoofDepth + 0.5f;
	static constexpr float FirstRoofShinglesDepth = 2.95f;
	static constexpr float FirstRoofShinglesHeight = 0.3f;
	static constexpr float FirstRoofShinglesOffsetX = 2.0f;

	static constexpr float FirstRoofLeftShinglesOffsetY = -1.0f;
	static constexpr float FirstRoofRightShinglesOffsetY = 1.0f;

	static constexpr float FirstRoofRightShinglesRotationX = -36.87f;
	static constexpr float FirstRoofLeftShinglesRotationX = 36.87f;

	static constexpr float SecondRoofWidth = 6.0f;
	static constexpr float SecondRoofDepth = 5.0f;
	static constexpr float SecondRoofHeight = 1.0f;
	static constexpr float SecondRoofOffsetY = 2.0f;
	static constexpr float RoofBaseHeight = WallHeight;

	static constexpr float RoofShinglesHeight = RoofBaseHeight + 0.75f;

	static constexpr float WindowWidth = 1.0f;
	static constexpr float WindowHeight = 1.0f;
	static constexpr float WindowThickness = 0.10f;
	static constexpr float WindowHalfThickness = WindowThickness / 2.0f;
	static constexpr float WindowBaseHeight = 0.75f;

	static constexpr float DoorWidth = 1.0f;
	static constexpr float DoorHeight = 1.5f;
	static constexpr float DoorThickness = 0.10f;
	static constexpr float DoorHalfThickness = DoorThickness / 2.0f;
	static constexpr float DoorBaseHeight = 0.5f;

	void AddBodies(std::vector<SceneObject>& objects) const;
	void AddRoofs(std::vector<SceneObject>& objects) const;
	void AddWindows(std::vector<SceneObject>& objects) const;
	void AddDoors(std::vector<SceneObject>& objects) const;

	glm::vec3 m_position;
};
