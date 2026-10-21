#pragma once

#include "model/Maze.h"
#include "model/PlayerCamera.h"
#include "view/GlfwWindow.h"
#include "view/SceneRenderer.h"

class Application
{
public:
	Application();
	int Run();

private:
	void Update(float deltaTime);
	void SetupInputHandlers();

	GlfwWindow m_window;
	Maze m_maze;
	PlayerCamera m_camera;
	SceneRenderer m_renderer;
	bool m_hasCursorPosition = false;
	double m_lastCursorX = 0.0;
};
