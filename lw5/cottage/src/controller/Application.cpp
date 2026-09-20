#include "controller/Application.h"

Application::Application()
	: m_window(800, 600, "Cottage")
{
	m_renderer.Initialize();
}

int Application::Run()
{
	while (!m_window.ShouldClose())
	{
		m_renderer.SetProjection(
			m_window.GetFramebufferWidth(),
			m_window.GetFramebufferHeight());
		m_renderer.Render(m_scene);
		m_window.SwapBuffers();
		m_window.PollEvents();
	}
	return 0;
}
