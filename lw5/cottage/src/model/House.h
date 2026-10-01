#pragma once

#include "model/Scene.h"

#include <vector>

class House
{
public:
	explicit House(Vector3 position);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;

private:
	void AddBodies(std::vector<SceneObject>& objects) const;
	void AddRoofs(std::vector<SceneObject>& objects) const;
	void AddWindows(std::vector<SceneObject>& objects) const;
	void AddDoors(std::vector<SceneObject>& objects) const;

	Vector3 m_position;
};
