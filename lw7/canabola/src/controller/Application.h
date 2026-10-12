#pragma once

#include "model/types/Camera.h"
#include "view/GlfwWindow.h"
#include "view/SceneRenderer.h"

class Application
{
public:
	Application();
	int Run();

private:
	void SetupInputHandlers();

	GlfwWindow m_window;
	Camera m_camera{
		.position = { 0.0f, 0.0f, 1.0f },
		.target = { 0.0f, 0.0f, 0.0f },
		.up = { 0.0f, 1.0f, 0.0f }
	};
	SceneRenderer m_renderer;
};
