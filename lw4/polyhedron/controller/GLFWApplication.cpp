#include "GLFWApplication.h"
#include <stdexcept>

GLFWApplication::GLFWApplication(const int width, const int height, const char* title)
{
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to init GLFW");
	}

	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!m_window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create window");
	}

	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);
	InitCallbacks();
}

GLFWApplication::~GLFWApplication()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void GLFWApplication::Run()
{
	OnInit();

	int w, h;
	glfwGetFramebufferSize(m_window, &w, &h);
	OnReshape(w, h);

	while (!glfwWindowShouldClose(m_window))
	{
		OnDisplay();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

void GLFWApplication::OnInit()
{
}

void GLFWApplication::OnDisplay()
{
}

void GLFWApplication::OnReshape(const int width, const int height)
{
	glViewport(0, 0, width, height);
}

void GLFWApplication::OnMouseButton(const int button, const int action, int mods)
{
}

void GLFWApplication::OnMouseMove(double x, double y)
{
}

void GLFWApplication::InitCallbacks() const
{
	glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, const int w, const int h) {
		static_cast<GLFWApplication*>(glfwGetWindowUserPointer(window))->OnReshape(w, h);
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* w, const double x, const double y) {
		static_cast<GLFWApplication*>(glfwGetWindowUserPointer(w))->OnMouseMove(x, y);
	});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* w, const int button, const int action, const int mods) {
		static_cast<GLFWApplication*>(glfwGetWindowUserPointer(w))->OnMouseButton(button, action, mods);
	});
}
