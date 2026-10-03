#include "model/FencePost.h"

#include "consts/CottageDimensions.h"
#include "data/Materials.h"

FencePost::FencePost(const glm::vec3 position)
	: m_position(position)
{
}

std::vector<SceneObject> FencePost::CreateObjects() const
{
	using namespace FenceDimensions;

	return {
		{ "Fence post",
			{ GeometryType::Box, PostSize, PostSize, PostHeight },
			{ m_position },
			Materials::Fence,
			{} }
	};
}
