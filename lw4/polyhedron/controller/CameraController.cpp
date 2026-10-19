#include "controller/CameraController.h"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <stdexcept>

namespace
{
constexpr float RadiansPerPixel = 0.01f;
constexpr float MinimumDistance = 1e-12f;
constexpr float ParallelDirectionThreshold = 0.9f;

constexpr glm::vec3 WorldUp{ 0.0f, 0.0f, 1.0f };
constexpr glm::vec3 WorldRight{ 1.0f, 0.0f, 0.0f };
} // namespace

CameraController::CameraController(Camera& camera)
	: m_camera(camera)
	, m_offset(m_camera.position - m_camera.target)
	, m_up(m_camera.up)
	, m_distance(glm::length(m_offset))
{
	if (m_distance <= MinimumDistance)
	{
		throw std::runtime_error("Camera position must differ from its target");
	}

	NormalizeOrientation();
	UpdateCamera();
}

void CameraController::OnMouseButton(
	const int button,
	const int action,
	const glm::dvec2 mousePosition)
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

	RotateHorizontally(-static_cast<float>(delta.x) * RadiansPerPixel);
	RotateVertically(-static_cast<float>(delta.y) * RadiansPerPixel);
	NormalizeOrientation();
	UpdateCamera();
}

glm::vec3 CameraController::CreateOrthogonalUp() const
{
	const glm::vec3 forward = -glm::normalize(m_offset);

	glm::vec3 orthogonalUp = m_up - glm::dot(m_up, forward) * forward;

	if (glm::dot(orthogonalUp, orthogonalUp) <= MinimumDistance)
	{
		const glm::vec3 fallback = std::abs(forward.z) < ParallelDirectionThreshold
			? WorldUp
			: WorldRight;
		orthogonalUp = fallback - glm::dot(fallback, forward) * forward;
	}
	return glm::normalize(orthogonalUp);
}

glm::vec3 CameraController::RotateVector(
	const glm::vec3& vector,
	const float angle,
	const glm::vec3& axis)
{
	const glm::mat4 rotation = glm::rotate(
		glm::mat4(1.0f),
		angle,
		glm::normalize(axis));
	return glm::mat3(rotation) * vector;
}

void CameraController::RotateHorizontally(const float angle)
{
	m_offset = RotateVector(m_offset, angle, m_up);
}

void CameraController::RotateVertically(const float angle)
{
	const glm::vec3 forward = -glm::normalize(m_offset);
	const glm::vec3 right = glm::normalize(glm::cross(forward, m_up));
	m_offset = RotateVector(m_offset, angle, right);
	m_up = RotateVector(m_up, angle, right);
}

void CameraController::NormalizeOrientation()
{
	m_offset = glm::normalize(m_offset) * m_distance;
	m_up = CreateOrthogonalUp();
}

void CameraController::UpdateCamera() const
{
	m_camera.position = m_camera.target + m_offset;
	m_camera.up = m_up;
}
