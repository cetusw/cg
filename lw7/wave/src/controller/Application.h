#pragma once

#include "view/GlfwWindow.h"
#include "view/SceneRenderer.h"

class Application
{
public:
	Application();
	int Run();

private:
	GlfwWindow m_window;
	SceneRenderer m_renderer;
};
