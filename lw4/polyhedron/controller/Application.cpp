#include "controller/Application.h"

#include "io/ObjParser.h"

#include <filesystem>

Application::Application(const std::string& modelPath)
	: m_window(1000, 750, "Polyhedron")
	, m_scene(ObjParser::Parse((std::filesystem::path(SOURCE_DIR) / modelPath).string()))
	, m_cameraController(m_scene.GetCamera())
{
	SceneRenderer::Initialize();
	SetupInputHandlers();
	SceneRenderer::SetProjection(
		m_window.GetFramebufferWidth(),
		m_window.GetFramebufferHeight());
}

int Application::Run() const
{
	while (!m_window.ShouldClose())
	{
		SceneRenderer::Render(m_scene);
		m_window.SwapBuffers();
		GlfwWindow::PollEvents();
	}
	return 0;
}

void Application::SetupInputHandlers()
{
	m_window.SetMouseButtonHandler(
		[this](const int button, const int action, const glm::dvec2 position) {
			m_cameraController.OnMouseButton(button, action, position);
		});
	m_window.SetCursorPositionHandler(
		[this](const glm::dvec2 position) {
			m_cameraController.OnCursorPosition(position);
		});
	m_window.SetFramebufferSizeHandler(
		[](const int width, const int height) {
			SceneRenderer::SetProjection(width, height);
		});
}
