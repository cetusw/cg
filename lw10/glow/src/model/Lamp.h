#pragma once

#include "types/Light.h"
#include "types/SceneObject.h"

#include <glm/vec3.hpp>
#include <vector>

class Lamp
{
public:
	Lamp(glm::vec3 position, glm::vec3 target);

	[[nodiscard]] std::vector<SceneObject> CreateObjects() const;
	[[nodiscard]] const SpotLight& GetLight() const;

private:
	static constexpr float Height = 2.5f;
	static constexpr float BaseWidth = 0.5f;
	static constexpr float BaseDepth = 0.5f;
	static constexpr float BaseHeight = 0.1f;
	static constexpr float PostWidth = 0.15f;
	static constexpr float PostDepth = 0.15f;
	static constexpr float PostHeight = Height - BaseHeight;
	static constexpr float HeadWidth = 0.6f;
	static constexpr float HeadDepth = 0.4f;
	static constexpr float HeadHeight = 0.3f;
	static constexpr float HalfHeadHeight = HeadHeight / 2.0f;

	[[nodiscard]] static glm::vec3 GetLightPosition(const glm::vec3& position);
	[[nodiscard]] static SpotLight CreateLight(
		const glm::vec3& position,
		const glm::vec3& target);

	glm::vec3 m_position;
	SpotLight m_light;
};
