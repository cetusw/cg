#include "model/House.h"

#include "model/CottageDimensions.h"
#include "model/Materials.h"

House::House(const Vector3 position)
	: m_position(position)
{
}

std::vector<SceneObject> House::CreateObjects() const
{
	std::vector<SceneObject> objects;
	objects.reserve(4);

	AddBodies(objects);
	AddRoofs(objects);

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
		{ GeometryType::Roof, FirstRoofWidth, FirstRoofDepth, FirstRoofHeight },
		{ { m_position.x + FirstRoofOffsetX, m_position.y, m_position.z + RoofBaseHeight }, { 0.0f, 0.0f, FirstRoofRotationZ } },
		Materials::Wall,
		"assets/brick.jpg"
	});
	objects.push_back({
		"Second roof",
		{ GeometryType::Roof, SecondRoofWidth, SecondRoofDepth, SecondRoofHeight },
		{ { m_position.x, m_position.y + SecondRoofOffsetY, m_position.z + RoofBaseHeight } },
		Materials::Wall,
		"assets/brick.jpg"
	});
}
