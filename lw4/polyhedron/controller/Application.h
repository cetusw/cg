#pragma once

#include "controller/CameraController.h"
#include "model/Scene.h"
#include "view/GlfwWindow.h"
#include "view/SceneRenderer.h"

#include <string>

class Application
{
public:
	explicit Application(const std::string& modelPath);
	int Run() const;

private:
	void SetupInputHandlers();

	GlfwWindow m_window;
	Scene m_scene;
	SceneRenderer m_renderer;
	CameraController m_cameraController;
};
