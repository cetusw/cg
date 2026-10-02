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
	void AddBodies(std::vector<SceneObject>& objects) const;
	void AddRoofs(std::vector<SceneObject>& objects) const;
	void AddWindows(std::vector<SceneObject>& objects) const;
	void AddDoors(std::vector<SceneObject>& objects) const;

	glm::vec3 m_position;
};
