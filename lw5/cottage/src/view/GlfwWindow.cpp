#define GLFW_INCLUDE_NONE

#include "view/GlfwWindow.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

GlfwWindow::GlfwWindow(const int width, const int height, const char* title)
{
	if (glfwInit() == GLFW_FALSE)
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (m_window == nullptr)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(m_window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(m_window);
		m_window = nullptr;
		glfwTerminate();
		throw std::runtime_error("Failed to initialize GLEW");
	}

	glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
	int framebufferWidth{};
	int framebufferHeight{};
	glfwGetFramebufferSize(m_window, &framebufferWidth, &framebufferHeight);
	FramebufferSizeCallback(m_window, framebufferWidth, framebufferHeight);
}

GlfwWindow::~GlfwWindow()
{
	if (m_window != nullptr)
	{
		glfwDestroyWindow(m_window);
	}
	glfwTerminate();
}

bool GlfwWindow::ShouldClose() const { return glfwWindowShouldClose(m_window) != GLFW_FALSE; }
void GlfwWindow::SwapBuffers() const { glfwSwapBuffers(m_window); }
void GlfwWindow::PollEvents() { glfwPollEvents(); }

void GlfwWindow::FramebufferSizeCallback(GLFWwindow*, const int width, const int height)
{
	glViewport(0, 0, width, height);
	SetProjection(width, height);
}

void GlfwWindow::SetProjection(const int width, const int height)
{
	const int safeHeight = height == 0 ? 1 : height;
	const double aspect = static_cast<double>(width) / static_cast<double>(safeHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspect, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}
