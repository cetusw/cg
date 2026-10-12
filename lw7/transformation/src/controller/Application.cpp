#include "controller/Application.h"

#include <GLFW/glfw3.h>

#include <cmath>

namespace
{
constexpr float MorphSpeed = 0.35f;
}

Application::Application()
	: m_window(1600, 1000, "Mobius Strip to Klein Bottle")
	, m_cameraController(m_camera)
{
	SceneRenderer::Initialize();
	SetupInputHandlers();
	SceneRenderer::SetProjection(
		m_window.GetFramebufferWidth(),
		m_window.GetFramebufferHeight());
}

int Application::Run()
{
	while (!m_window.ShouldClose())
	{
		const auto time = static_cast<float>(glfwGetTime());

		const float morph = (1.0f - std::cos(time * MorphSpeed)) / 2.0f;

		m_renderer.Render(m_camera, morph);
		m_window.SwapBuffers();
		GlfwWindow::PollEvents();
	}
	return 0;
}

void Application::SetupInputHandlers()
{
	m_window.SetMouseButtonHandler(
		[this](const int button, const int action, const glm::dvec2 mousePosition) {
			m_cameraController.OnMouseButton(button, action, mousePosition);
		});
	m_window.SetCursorPositionHandler(
		[this](const glm::dvec2 mousePosition) {
			m_cameraController.OnCursorPosition(mousePosition);
		});
	m_window.SetFramebufferSizeHandler(
		[](const int width, const int height) {
			SceneRenderer::SetProjection(width, height);
		});
}
