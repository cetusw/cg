#include "model/Cottage.h"

Cottage::Cottage(const glm::vec3 position)
	: m_position(position)
	, m_house(position)
	, m_garage(position + GarageOffset)
	, m_porch(position + PorchOffset)
	, m_fence(position)
	, m_lamps{
		Lamp(
			position + Lamp1PositionOffset,
			position + Lamp1TargetOffset),
		Lamp(
			position + Lamp2PositionOffset,
			position + Lamp2TargetOffset)
	}
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

	const std::vector<SceneObject> fenceObjects = m_fence.CreateObjects();
	objects.insert(
		objects.end(),
		fenceObjects.begin(),
		fenceObjects.end());

	for (const Lamp& lamp : m_lamps)
	{
		const std::vector<SceneObject> lampObjects = lamp.CreateObjects();
		objects.insert(
			objects.end(),
			lampObjects.begin(),
			lampObjects.end());
	}

	return objects;
}

std::size_t Cottage::GetSpotLightCount() const
{
	return m_lamps.size();
}

const SpotLight& Cottage::GetSpotLight(const std::size_t index) const
{
	return m_lamps[index].GetLight();
}
