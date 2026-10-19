#pragma once

#include "model/Camera.h"

#include <glm/glm.hpp>

class CameraController
{
public:
	explicit CameraController(Camera& camera);
	void OnMouseButton(int button, int action, glm::dvec2 mousePosition);
	void OnCursorPosition(glm::dvec2 mousePosition);

private:
	[[nodiscard]] glm::vec3 CreateOrthogonalUp() const;
	[[nodiscard]] static glm::vec3 RotateVector(
		const glm::vec3& vector,
		float angle,
		const glm::vec3& axis);
	void RotateHorizontally(float angle);
	void RotateVertically(float angle);
	void NormalizeOrientation();
	void UpdateCamera() const;

	Camera& m_camera;
	bool m_isRotating = false;
	glm::dvec2 m_lastMousePosition{};
	glm::vec3 m_offset{};
	glm::vec3 m_up{};
	float m_distance{};
};
