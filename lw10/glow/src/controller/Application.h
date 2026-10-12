#pragma once

#include "controller/CameraController.h"
#include "model/Scene.h"
#include "view/GlfwWindow.h"
#include "view/GlowRenderer.h"
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
	GlowRenderer m_glowRenderer;
	CameraController m_cameraController;
	bool m_isGlowEnabled = true;
	bool m_isLightMotionBlurEnabled = true;
};
