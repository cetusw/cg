#include "controller/Application.h"

#include <GLFW/glfw3.h>

#include <algorithm>

namespace
{
constexpr float MaximumDeltaTime = 0.1f;
} // namespace

Application::Application()
	: m_window(1280, 720, "Maze")
{
	SceneRenderer::Initialize();
	SetupInputHandlers();
	m_window.SetCursorDisabled();
	SceneRenderer::SetProjection(m_window.GetFramebufferWidth(), m_window.GetFramebufferHeight());
}

int Application::Run()
{
	double previousTime = glfwGetTime();
	while (!m_window.ShouldClose())
	{
		const double currentTime = glfwGetTime();
		const float deltaTime = std::min(static_cast<float>(currentTime - previousTime), MaximumDeltaTime);
		previousTime = currentTime;
		const bool isFocused = m_window.IsFocused();
		if (!isFocused)
		{
			m_hasCursorPosition = false;
		}
		Update(isFocused ? deltaTime : 0.0f);
		SceneRenderer::Render(m_maze, m_camera);
		m_window.SwapBuffers();
		GlfwWindow::PollEvents();
	}
	return 0;
}

void Application::Update(const float deltaTime)
{
	if (m_window.IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		m_window.RequestClose();
	}

	const float forwardInput = (m_window.IsKeyPressed(GLFW_KEY_W) ? 1.0f : 0.0f)
		- (m_window.IsKeyPressed(GLFW_KEY_S) ? 1.0f : 0.0f);
	const float rightInput = (m_window.IsKeyPressed(GLFW_KEY_D) ? 1.0f : 0.0f) -
		(m_window.IsKeyPressed(GLFW_KEY_A) ? 1.0f : 0.0f);
	m_camera.Move(forwardInput, rightInput, deltaTime, m_maze);
}

void Application::SetupInputHandlers()
{
	m_window.SetCursorPositionHandler(
		[this](const glm::dvec2 mousePosition) {
			if (!m_hasCursorPosition)
			{
				m_lastCursorX = mousePosition.x;
				m_hasCursorPosition = true;
				return;
			}
			m_camera.Turn(static_cast<float>(mousePosition.x - m_lastCursorX));
			m_lastCursorX = mousePosition.x;
		});
	m_window.SetFramebufferSizeHandler(
		[](const int width, const int height) {
			SceneRenderer::SetProjection(width, height);
		});
}
