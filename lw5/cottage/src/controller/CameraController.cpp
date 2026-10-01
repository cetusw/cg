#include "controller/CameraController.h"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <cmath>

namespace CameraControl
{
inline constexpr float MouseSensitivityRadiansPerPixel = 0.005f;
inline constexpr float Pi = 3.14159265358979323846f;
inline constexpr float MaxPitchRadians = 89.0f * Pi / 180.0f;
} // namespace CameraControl

CameraController::CameraController(Camera& camera)
	: m_camera(camera)
{
	const float offsetX = m_camera.position.x - m_camera.target.x;
	const float offsetY = m_camera.position.y - m_camera.target.y;
	const float offsetZ = m_camera.position.z - m_camera.target.z;
	m_distance = std::sqrt(offsetX * offsetX + offsetY * offsetY + offsetZ * offsetZ);

	if (m_distance > 0.0f)
	{
		m_pitchRadians = std::asin(offsetZ / m_distance);
		m_yawRadians = std::atan2(offsetY, offsetX);
	}
}

void CameraController::OnMouseButton(const int button, const int action)
{
	if (button != GLFW_MOUSE_BUTTON_LEFT)
	{
		return;
	}

	m_rotating = action == GLFW_PRESS;
	m_hasMousePosition = false;
}

void CameraController::OnCursorPosition(const double x, const double y)
{
	if (!m_rotating)
	{
		return;
	}

	if (!m_hasMousePosition)
	{
		m_lastMouseX = x;
		m_lastMouseY = y;
		m_hasMousePosition = true;
		return;
	}

	const double deltaX = x - m_lastMouseX;
	const double deltaY = y - m_lastMouseY;
	m_lastMouseX = x;
	m_lastMouseY = y;

	m_yawRadians += static_cast<float>(deltaX) * CameraControl::MouseSensitivityRadiansPerPixel;
	m_pitchRadians -= static_cast<float>(deltaY) * CameraControl::MouseSensitivityRadiansPerPixel;
	m_pitchRadians = std::clamp(
		m_pitchRadians,
		-CameraControl::MaxPitchRadians,
		CameraControl::MaxPitchRadians);
	UpdateCamera();
}

void CameraController::UpdateCamera()
{
	const float horizontalDistance = m_distance * std::cos(m_pitchRadians);
	m_camera.position = {
		m_camera.target.x + horizontalDistance * std::cos(m_yawRadians),
		m_camera.target.y + horizontalDistance * std::sin(m_yawRadians),
		m_camera.target.z + m_distance * std::sin(m_pitchRadians)
	};
}
