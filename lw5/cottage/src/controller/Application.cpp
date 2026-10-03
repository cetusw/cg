#include "controller/Application.h"

Application::Application()
	: m_window(800, 600, "Cottage")
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
	while (!m_window.ShouldClose())
	{
		m_renderer.Render(m_scene);
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
