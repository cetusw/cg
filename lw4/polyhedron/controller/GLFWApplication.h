#pragma once
#include <GLFW/glfw3.h>

class GLFWApplication
{
public:
	GLFWApplication(int width, int height, const char* title);
	virtual ~GLFWApplication();

	void Run();

protected:
	GLFWwindow* m_window;

	virtual void OnInit();
	virtual void OnDisplay();
	virtual void OnReshape(int width, int height);
	virtual void OnMouseButton(int button, int action, [[maybe_unused]] int mods);
	virtual void OnMouseMove(double x, double y);

private:
	void InitCallbacks() const;
};
