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

		m_renderer.Render(
			m_waveCenter,
			elapsedTime,
			m_isWaveActive,
			m_window.GetFramebufferWidth(),
			m_window.GetFramebufferHeight());
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
	const int framebufferWidth = m_window.GetFramebufferWidth();
	const int framebufferHeight = m_window.GetFramebufferHeight();

	if (windowSize.x <= 0 || windowSize.y <= 0 || framebufferWidth <= 0 || framebufferHeight <= 0)
	{
		return;
	}

	const glm::dvec2 framebufferPosition = {
		mousePosition.x * framebufferWidth / windowSize.x,
		framebufferHeight - mousePosition.y * framebufferHeight / windowSize.y
	};

	glm::vec2 textureCoordinates;
	if (!m_renderer.TryGetTextureCoordinates(
		framebufferPosition,
		framebufferWidth,
		framebufferHeight,
		textureCoordinates))
	{
		return;
	}

	m_waveCenter = textureCoordinates;
	m_waveStartTime = static_cast<float>(glfwGetTime());
	m_isWaveActive = true;
	m_renderer.SwapTextures();
}
