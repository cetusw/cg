#pragma once

#include "view/GlfwWindow.h"
#include "view/SceneRenderer.h"

class Application
{
public:
	Application();
	int Run();

private:
	void HandleMouseButton(int button, int action, glm::dvec2 mousePosition);

	GlfwWindow m_window;
	SceneRenderer m_renderer;

	glm::vec2 m_waveCenter = { 0.5f, 0.5f };
	float m_waveStartTime = 0.0f;
	bool m_isWaveActive = false;
};
