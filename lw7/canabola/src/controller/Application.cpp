#include "controller/Application.h"

Application::Application()
	: m_window(1600, 1000, "Canabola")
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
		GlfwWindow::PollEvents();
		m_renderer.Render(m_camera);
		m_window.SwapBuffers();
	}
	return 0;
}

void Application::SetupInputHandlers()
{
	m_window.SetFramebufferSizeHandler(
		[](const int width, const int height) {
			SceneRenderer::SetProjection(width, height);
		});
}
