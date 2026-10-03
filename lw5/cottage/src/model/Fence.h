#pragma once

#include "model/FenceSection.h"

#include <glm/vec3.hpp>
#include <vector>

class Fence
{
public:
	explicit Fence(glm::vec3 position);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;

private:
	void AddBackFence(std::vector<SceneObject>& objects) const;
	void AddRightFence(std::vector<SceneObject>& objects) const;
	void AddFrontFence(std::vector<SceneObject>& objects) const;
	void AddLeftFence(std::vector<SceneObject>& objects) const;
	static void AddSection(
		std::vector<SceneObject>& objects,
		glm::vec3 position,
		FenceDirection direction);
	static void AddPost(
		std::vector<SceneObject>& objects,
		glm::vec3 position);

	glm::vec3 m_position;
};
