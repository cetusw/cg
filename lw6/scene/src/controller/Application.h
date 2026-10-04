#pragma once

#include "controller/CameraController.h"
#include "model/Scene.h"
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
	Scene m_scene;
	SceneRenderer m_renderer;
	CameraController m_cameraController;
};
