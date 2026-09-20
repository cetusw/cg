#include "model/Cottage.h"

#include "model/CottageDimensions.h"

Cottage::Cottage(const Vector3 position)
	: m_position(position)
	, m_house(position)
	, m_garage({ position.x + CottageDimensions::GarageOffset.x,
		  position.y + CottageDimensions::GarageOffset.y,
		  position.z + CottageDimensions::GarageOffset.z })
	, m_porch({ position.x + CottageDimensions::PorchOffset.x,
		  position.y + CottageDimensions::PorchOffset.y,
		  position.z + CottageDimensions::PorchOffset.z })
{
}

std::vector<SceneObject> Cottage::CreateObjects() const
{
	std::vector<SceneObject> objects;

	const std::vector<SceneObject> houseObjects = m_house.CreateObjects();
	objects.insert(
		objects.end(),
		houseObjects.begin(),
		houseObjects.end());

	const std::vector<SceneObject> garageObjects = m_garage.CreateObjects();
	objects.insert(
		objects.end(),
		garageObjects.begin(),
		garageObjects.end());

	const std::vector<SceneObject> porchObjects = m_porch.CreateObjects();
	objects.insert(
		objects.end(),
		porchObjects.begin(),
		porchObjects.end());

	return objects;
}
