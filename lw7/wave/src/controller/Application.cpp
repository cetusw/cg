#include "controller/Application.h"

#include <GLFW/glfw3.h>

Application::Application()
	: m_window(1600, 1000, "Wave")
{
	m_window.SetMouseButtonHandler(
		[this](const int button, const int action, const glm::dvec2 mousePosition) {
			HandleMouseButton(button, action, mousePosition);
		});
}

int Application::Run()
{
	while (!m_window.ShouldClose())
	{
		const auto time = static_cast<float>(glfwGetTime());
		const float elapsedTime = time - m_waveStartTime;

		const float aspectRatio = m_window.GetWindowSize().x / m_window.GetWindowSize().y;

		m_renderer.Render(
			m_waveCenter,
			elapsedTime,
			m_isWaveActive,
			aspectRatio);
		m_window.SwapBuffers();
		GlfwWindow::PollEvents();
	}
	return 0;
}

void Application::HandleMouseButton(const int button, const int action, const glm::dvec2 mousePosition)
{
	if (button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_PRESS)
	{
		return;
	}

	const glm::vec2 windowSize = m_window.GetWindowSize();

	if (windowSize.x <= 0 || windowSize.y <= 0)
	{
		return;
	}

	const auto u = static_cast<float>(mousePosition.x / windowSize.x);
	const auto v = 1.0f - static_cast<float>(mousePosition.y / windowSize.y);

	m_waveCenter = { u, v };
	m_waveStartTime = static_cast<float>(glfwGetTime());
	m_isWaveActive = true;
	m_renderer.SwapTextures();
}