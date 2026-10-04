#pragma once

#include <glm/glm.hpp>

#include "model/types/Camera.h"

class CameraController
{
public:
	explicit CameraController(Camera& camera);

	void OnMouseButton(int button, int action, glm::dvec2 mousePosition);
	void OnCursorPosition(glm::dvec2 mousePosition);

private:
	void UpdateCamera() const;

	Camera& m_camera;
	bool m_isRotating = false;
	glm::dvec2 m_lastMousePosition{};
	float m_yawRadians{};
	float m_pitchRadians{};
	float m_distance{};
};
