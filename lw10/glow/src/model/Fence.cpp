#include "model/Fence.h"

#include "model/FencePost.h"
#include "model/FenceSection.h"

Fence::Fence(const glm::vec3 position)
	: m_position(position)
{
}

std::vector<SceneObject> Fence::CreateObjects() const
{
	std::vector<SceneObject> objects;

	AddBackFence(objects);
	AddRightFence(objects);
	AddFrontFence(objects);
	AddLeftFence(objects);

	return objects;
}

void Fence::AddBackFence(std::vector<SceneObject>& objects) const
{
	for (int sectionIndex = 0; sectionIndex < WidthSectionCount; sectionIndex++)
	{
		const glm::vec3 position{
			m_position.x - HalfWidth + sectionIndex * SectionLength,
			m_position.y - HalfDepth,
			m_position.z
		};
		AddSection(objects, position, FenceDirection::PositiveX);
	}
}

void Fence::AddRightFence(std::vector<SceneObject>& objects) const
{
	for (int sectionIndex = 0; sectionIndex < DepthSectionCount; ++sectionIndex)
	{
		const glm::vec3 position{
			m_position.x + HalfWidth,
			m_position.y - HalfDepth + sectionIndex * SectionLength,
			m_position.z
		};
		AddSection(objects, position, FenceDirection::PositiveY);
	}
}

void Fence::AddFrontFence(std::vector<SceneObject>& objects) const
{
	for (int sectionIndex = 0; sectionIndex < WidthSectionCount; ++sectionIndex)
	{
		const glm::vec3 position{
			m_position.x + HalfWidth - sectionIndex * SectionLength,
			m_position.y + HalfDepth,
			m_position.z
		};
		const bool isDrivewayGap = sectionIndex >= DrivewayGapStartSection
			&& sectionIndex < DrivewayGapStartSection + DrivewayGapSectionCount;
		const bool isEntranceGap = sectionIndex >= EntranceGapStartSection
			&& sectionIndex < EntranceGapStartSection + EntranceGapSectionCount;

		if (isDrivewayGap || isEntranceGap)
		{
			if (sectionIndex == DrivewayGapStartSection
				|| sectionIndex == EntranceGapStartSection)
			{
				AddPost(objects, position);
			}
			continue;
		}

		AddSection(objects, position, FenceDirection::NegativeX);
	}
}

void Fence::AddLeftFence(std::vector<SceneObject>& objects) const
{
	for (int sectionIndex = 0; sectionIndex < DepthSectionCount; ++sectionIndex)
	{
		const glm::vec3 position{
			m_position.x - HalfWidth,
			m_position.y + HalfDepth - sectionIndex * SectionLength,
			m_position.z
		};
		AddSection(objects, position, FenceDirection::NegativeY);
	}
}

void Fence::AddSection(
	std::vector<SceneObject>& objects,
	const glm::vec3 position,
	const FenceDirection direction)
{
	const FenceSection section(position, direction);
	const std::vector<SceneObject> sectionObjects = section.CreateObjects();
	objects.insert(objects.end(), sectionObjects.begin(), sectionObjects.end());
}

void Fence::AddPost(
	std::vector<SceneObject>& objects,
	const glm::vec3 position)
{
	const FencePost post(position);
	const std::vector<SceneObject> postObjects = post.CreateObjects();
	objects.insert(objects.end(), postObjects.begin(), postObjects.end());
}
