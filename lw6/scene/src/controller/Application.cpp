#include "controller/Application.h"

#include <algorithm>
#include <chrono>

namespace
{
constexpr float MaxDeltaTime = 0.1f;
}

Application::Application()
	: m_window(1600, 1000, "3ds viewer")
	, m_cameraController(m_scene.GetCamera())
{
	SceneRenderer::Initialize();
	SetupInputHandlers();
	SceneRenderer::SetProjection(m_window.GetFramebufferWidth(), m_window.GetFramebufferHeight());
}

int Application::Run()
{
	auto previousTime = std::chrono::steady_clock::now(); // TODO подумать над уместностью названия
	while (!m_window.ShouldClose())
	{
		const auto currentTime = std::chrono::steady_clock::now();
		const float deltaTime = std::min(std::chrono::duration<float>(currentTime - previousTime).count(), MaxDeltaTime); // TODO что возвращает count?
		previousTime = currentTime;

		m_scene.Update(deltaTime);
		m_renderer.Render(m_scene);
		m_window.SwapBuffers();
		GlfwWindow::PollEvents();
	}
	return 0;
}

void Application::SetupInputHandlers()
{
	m_window.SetMouseButtonHandler([this](const int button, const int action, const glm::dvec2 mousePosition) {
		m_cameraController.OnMouseButton(button, action, mousePosition);
	});
	m_window.SetCursorPositionHandler([this](const glm::dvec2 mousePosition) {
		m_cameraController.OnCursorPosition(mousePosition);
	});
	m_window.SetFramebufferSizeHandler([](const int width, const int height) {
		SceneRenderer::SetProjection(width, height);
	});
}
