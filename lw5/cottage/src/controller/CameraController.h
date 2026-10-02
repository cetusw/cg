#pragma once

#include "../model/types/Camera.h"

class CameraController
{
public:
	explicit CameraController(Camera& camera);

	void OnMouseButton(int button, int action);
	void OnCursorPosition(double x, double y);

private:
	void UpdateCamera();

	Camera& m_camera;
	bool m_rotating = false;
	bool m_hasMousePosition = false;
	double m_lastMouseX = 0.0;
	double m_lastMouseY = 0.0;
	float m_yawRadians = 0.0f;
	float m_pitchRadians = 0.0f;
	float m_distance = 0.0f;
};
