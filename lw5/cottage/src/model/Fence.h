#pragma once

#include "model/FenceSection.h"

#include <glm/vec3.hpp>
#include <vector>

class Fence
{
public:
	static constexpr float SectionLength = 2.0f;
	static constexpr float HalfSectionLength = SectionLength / 2.0f;
	static constexpr int WidthSectionCount = 8;
	static constexpr int DepthSectionCount = 6;
	static constexpr float HalfWidth = WidthSectionCount * HalfSectionLength;
	static constexpr float HalfDepth = DepthSectionCount * HalfSectionLength;

	static constexpr float PanelHeight = 1.0f;
	static constexpr float PanelThickness = 0.15f;
	static constexpr float PostSize = 0.2f;
	static constexpr float PostHeight = 1.3f;

	static constexpr int DrivewayGapStartSection = 0;
	static constexpr int DrivewayGapSectionCount = 2;
	static constexpr int EntranceGapStartSection = 3;
	static constexpr int EntranceGapSectionCount = 1;

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
