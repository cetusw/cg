#pragma once

#include "view/GlfwWindow.h"
#include "view/SceneRenderer.h"

class Application
{
public:
	Application();
	[[nodiscard]] int Run() const;

private:
	GlfwWindow m_window;
	SceneRenderer m_renderer;
};
