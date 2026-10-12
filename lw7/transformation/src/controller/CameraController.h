#pragma once

#include "model/types/Camera.h"

#include <glm/glm.hpp>

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
	float m_yawRadians = 0.0f;
	float m_pitchRadians = 0.0f;
	float m_distance = 0.0f;
};
