#include "model/FencePost.h"

#include "data/Materials.h"
#include "model/Fence.h"

FencePost::FencePost(const glm::vec3 position)
	: m_position(position)
{
}

std::vector<SceneObject> FencePost::CreateObjects() const
{
	return {
		{ "Fence post",
			{ GeometryType::Box, Fence::PostSize, Fence::PostSize, Fence::PostHeight },
			{ m_position },
			Materials::Fence,
			{} }
	};
}
