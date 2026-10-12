#include "controller/Application.h"

#include <GLFW/glfw3.h>

Application::Application()
	: m_window(2300, 1500, "Cottage")
	, m_glowRenderer(
		  m_window.GetFramebufferWidth(),
		  m_window.GetFramebufferHeight())
	, m_cameraController(m_scene.GetCamera())
{
	SceneRenderer::Initialize();
	SetupInputHandlers();
	SceneRenderer::SetProjection(
		m_window.GetFramebufferWidth(),
		m_window.GetFramebufferHeight());
}

int Application::Run()
{
	double previousTime = glfwGetTime();

	while (!m_window.ShouldClose())
	{
		const double currentTime = glfwGetTime();
		const float deltaTime = static_cast<float>(currentTime - previousTime);
		previousTime = currentTime;

		if (m_window.GetFramebufferWidth() > 0 && m_window.GetFramebufferHeight() > 0)
		{
			m_renderer.Render(m_scene);
			if (m_isGlowEnabled)
			{
				m_glowRenderer.Render(m_scene, m_renderer, deltaTime);
			}
			m_window.SwapBuffers();
		}
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
		[this](const int width, const int height) {
			SceneRenderer::SetProjection(width, height);
			m_glowRenderer.Resize(width, height);
		});
	m_window.SetKeyHandler(
		[this](const int key, const int action) {
			if (key == GLFW_KEY_G && action == GLFW_PRESS)
			{
				m_isGlowEnabled = !m_isGlowEnabled;
				if (m_isGlowEnabled)
				{
					m_glowRenderer.ResetLightMotionBlur();
				}
			}
			if (key == GLFW_KEY_L && action == GLFW_PRESS)
			{
				m_isLightMotionBlurEnabled = !m_isLightMotionBlurEnabled;
				m_glowRenderer.SetLightMotionBlurEnabled(m_isLightMotionBlurEnabled);
			}
		});
}
