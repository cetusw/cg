#pragma once

#include "model/Scene.h"
#include "view/GlfwWindow.h"
#include "view/SceneRenderer.h"

class Application
{
public:
	Application();
	int Run();

private:
	GlfwWindow m_window;
	Scene m_scene;
	SceneRenderer m_renderer;
};
