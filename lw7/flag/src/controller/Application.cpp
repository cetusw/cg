#include "controller/Application.h"

Application::Application()
	: m_window(1600, 800, "Ring")
{
}

int Application::Run()
{
	while (!m_window.ShouldClose())
	{
		GlfwWindow::PollEvents();
		GlfwWindow::PollEvents();

		const glm::ivec2 framebufferSize = m_window.GetFramebufferSize();

		m_renderer.Render(
			framebufferSize.x,
			framebufferSize.y);
		m_window.SwapBuffers();
	}
	return 0;
}
