#include "controller/Application.h"

Application::Application()
	: m_window(1600, 800, "Ring")
{
}

int Application::Run() const
{
	while (!m_window.ShouldClose())
	{
		m_renderer.Render(
			m_window.GetFramebufferWidth(),
			m_window.GetFramebufferHeight());
		m_window.SwapBuffers();
		GlfwWindow::PollEvents();
	}
	return 0;
}
