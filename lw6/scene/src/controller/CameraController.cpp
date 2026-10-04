#include "controller/CameraController.h"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <cmath>
#include <glm/geometric.hpp>
#include <numbers>

namespace CameraSettings
{
inline constexpr float RadiansPerPixel = 0.01f;
inline constexpr float MaxPitchRadians = 89.9f * std::numbers::pi / 180.0f;
inline constexpr float MinPitchRadians = 0.1f * std::numbers::pi / 180.0f;
} // namespace CameraSettings

CameraController::CameraController(Camera& camera)
	: m_camera(camera)
{
	const glm::vec3 targetToCamera = m_camera.position - m_camera.target;
	m_distance = glm::length(targetToCamera);
	if (m_distance > 0.0f)
	{
		m_pitchRadians = std::asin(targetToCamera.z / m_distance);
		m_yawRadians = std::atan2(targetToCamera.y, targetToCamera.x);
	}
}

void CameraController::OnMouseButton(const int button, const int action, const glm::dvec2 mousePosition)
{
	if (button != GLFW_MOUSE_BUTTON_LEFT)
	{
		return;
	}

	m_isRotating = action == GLFW_PRESS;
	if (m_isRotating)
	{
		m_lastMousePosition = mousePosition;
	}
}

void CameraController::OnCursorPosition(const glm::dvec2 mousePosition)
{
	if (!m_isRotating)
	{
		return;
	}

	const glm::dvec2 delta = mousePosition - m_lastMousePosition;
	m_lastMousePosition = mousePosition;
	m_yawRadians -= static_cast<float>(delta.x) * CameraSettings::RadiansPerPixel;
	m_pitchRadians += static_cast<float>(delta.y) * CameraSettings::RadiansPerPixel;
	m_pitchRadians = std::clamp(m_pitchRadians, CameraSettings::MinPitchRadians, CameraSettings::MaxPitchRadians);
	UpdateCamera();
}

void CameraController::UpdateCamera() const
{
	const float horizontalDistance = m_distance * std::cos(m_pitchRadians);
	m_camera.position = {
		m_camera.target.x + horizontalDistance * std::cos(m_yawRadians),
		m_camera.target.y + horizontalDistance * std::sin(m_yawRadians),
		m_camera.target.z + m_distance * std::sin(m_pitchRadians)
	};
}
