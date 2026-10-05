#define GLFW_INCLUDE_NONE

#include "view/GlfwWindow.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <utility>

GlfwWindow::GlfwWindow(const int width, const int height, const char* title)
{
	InitializeGlfw();
	CreateWindow(width, height, title);
	InitializeOpenGL();
	SetupCallbacks();
}

GlfwWindow::~GlfwWindow()
{
	if (m_window != nullptr)
	{
		glfwDestroyWindow(m_window);
	}
	glfwTerminate();
}

bool GlfwWindow::ShouldClose() const
{
	return glfwWindowShouldClose(m_window) != GLFW_FALSE;
}

void GlfwWindow::SwapBuffers() const
{
	glfwSwapBuffers(m_window);
}

void GlfwWindow::PollEvents()
{
	glfwPollEvents();
}

void GlfwWindow::SetMouseButtonHandler(MouseButtonHandler handler)
{
	m_mouseButtonHandler = std::move(handler);
}

void GlfwWindow::SetCursorPositionHandler(CursorPositionHandler handler)
{
	m_cursorPositionHandler = std::move(handler);
}

void GlfwWindow::SetFramebufferSizeHandler(FramebufferSizeHandler handler)
{
	m_framebufferSizeHandler = std::move(handler);
}

int GlfwWindow::GetFramebufferWidth() const
{
	return m_framebufferWidth;
}

int GlfwWindow::GetFramebufferHeight() const
{
	return m_framebufferHeight;
}

void GlfwWindow::InitializeGlfw()
{
	if (glfwInit() == GLFW_FALSE)
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
}

void GlfwWindow::CreateWindow(
	const int width,
	const int height,
	const char* title)
{
	m_window = glfwCreateWindow(
		width,
		height,
		title,
		nullptr,
		nullptr);

	if (m_window == nullptr)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwSetWindowUserPointer(m_window, this);
}

void GlfwWindow::InitializeOpenGL()
{
	glfwMakeContextCurrent(m_window);

	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		throw std::runtime_error("Failed to initialize GLEW");
	}
}

void GlfwWindow::SetupCallbacks()
{
	glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
	glfwSetCursorPosCallback(m_window, CursorPositionCallback);

	glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);

	int framebufferWidth;
	int framebufferHeight;
	glfwGetFramebufferSize(m_window, &framebufferWidth, &framebufferHeight);
	FramebufferSizeCallback(m_window, framebufferWidth, framebufferHeight);
}

void GlfwWindow::MouseButtonCallback(GLFWwindow* window, const int button, const int action, int)
{
	const auto* self = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
	glm::dvec2 mousePosition;
	glfwGetCursorPos(window, &mousePosition.x, &mousePosition.y);
	if (self != nullptr && self->m_mouseButtonHandler)
	{
		self->m_mouseButtonHandler(button, action, mousePosition);
	}
}

void GlfwWindow::CursorPositionCallback(GLFWwindow* window, const double x, const double y)
{
	const auto* self = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
	if (self != nullptr && self->m_cursorPositionHandler)
	{
		self->m_cursorPositionHandler(glm::dvec2{ x, y });
	}
}

void GlfwWindow::FramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);

	auto* self = static_cast<GlfwWindow*>(
		glfwGetWindowUserPointer(window));

	if (self == nullptr)
	{
		return;
	}

	self->m_framebufferWidth = width;
	self->m_framebufferHeight = height;

	if (self->m_framebufferSizeHandler)
	{
		self->m_framebufferSizeHandler(width, height);
	}
}
