#pragma once

#include "controller/CameraController.h"
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
		.position = { 5.0f, 5.0f, 3.5f },
		.target = { 0.0f, 0.0f, 0.0f },
		.up = { 0.0f, 0.0f, 1.0f }
	};
	SceneRenderer m_renderer;
	CameraController m_cameraController;
};
