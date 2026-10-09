#include "controller/Application.h"

#include <GLFW/glfw3.h>

Application::Application()
	: m_window(1600, 1000, "Wave")
{
}

int Application::Run()
{
	while (!m_window.ShouldClose())
	{
		const auto time = static_cast<float>(glfwGetTime());

		m_renderer.Render(time);
		m_window.SwapBuffers();
		GlfwWindow::PollEvents();
	}
	return 0;
}
