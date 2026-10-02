#include "model/House.h"

#include "consts/CottageDimensions.h"
#include "data/Materials.h"

House::House(const glm::vec3 position)
	: m_position(position)
{
}

std::vector<SceneObject> House::CreateObjects() const
{
	std::vector<SceneObject> objects;
	objects.reserve(7); // TODO понять, зачем так делать и сделать число явным

	AddBodies(objects);
	AddRoofs(objects);
	AddWindows(objects);
	AddDoors(objects);

	return objects;
}

void House::AddBodies(std::vector<SceneObject>& objects) const
{
	using namespace HouseDimensions;

	objects.push_back({
		"First Body",
		{ GeometryType::Box, FirstBodyWidth, FirstBodyDepth, WallHeight },
		{ { m_position.x + BodyOffsetX, m_position.y, m_position.z } },
		Materials::Wall,
		"assets/concrete.jpg"
	});
	objects.push_back({
		"Second Body",
		{ GeometryType::Box, SecondBodyWidth, SecondBodyDepth, WallHeight },
		{ { m_position.x - BodyOffsetX, m_position.y + SecondBodyOffsetY, m_position.z } },
		Materials::Wall,
		"assets/concrete.jpg"
	});
}

void House::AddRoofs(std::vector<SceneObject>& objects) const
{
	using namespace HouseDimensions;

	objects.push_back({
		"First roof",
		{ GeometryType::TriangularPrism, FirstRoofWidth, FirstRoofDepth, FirstRoofHeight },
		{ { m_position.x + FirstRoofOffsetX, m_position.y, m_position.z + RoofBaseHeight }, { 0.0f, 0.0f, FirstRoofRotationZ } },
		Materials::Wall,
		"assets/brick.jpg"
	});
	objects.push_back({
		"Second roof",
		{ GeometryType::TriangularPrism, SecondRoofWidth, SecondRoofDepth, SecondRoofHeight },
		{ { m_position.x, m_position.y + SecondRoofOffsetY, m_position.z + RoofBaseHeight } },
		Materials::Wall,
		"assets/brick.jpg"
	});
}

void House::AddWindows(std::vector<SceneObject>& objects) const
{
	using namespace HouseDimensions;

	objects.push_back({
		"House side window",
		{ GeometryType::Box, WindowThickness, WindowWidth, WindowHeight },
		{ { m_position.x + BodyOffsetX + FirstBodyWidth / 2.0f + WindowThickness / 2.0f, m_position.y, m_position.z + WindowBaseHeight } },
		Materials::Window,
		{}
	});
	objects.push_back({
		"House back window",
		{ GeometryType::Box, WindowWidth, WindowThickness, WindowHeight },
		{ { m_position.x - BodyOffsetX, m_position.y + SecondBodyOffsetY - SecondBodyDepth / 2.0f - WindowThickness / 2.0f, m_position.z + WindowBaseHeight } },
		Materials::Window,
		{}
	});
}

void House::AddDoors(std::vector<SceneObject>& objects) const
{
	using namespace HouseDimensions;

	objects.push_back({
		"House entrance door",
		{ GeometryType::Box, DoorWidth, DoorThickness, DoorHeight },
		{ { m_position.x + BodyOffsetX, m_position.y + FirstBodyDepth / 2.0f + DoorThickness / 2.0f, m_position.z + DoorBaseHeight } },
		Materials::Door,
		{}
	});
}
