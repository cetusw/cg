#pragma once

#include <functional>
#include <glm/glm.hpp>

struct GLFWwindow;

class GlfwWindow
{
public:
	using MouseButtonHandler = std::function<void(int, int, glm::dvec2)>;
	using CursorPositionHandler = std::function<void(glm::dvec2)>;
	using FramebufferSizeHandler = std::function<void(int, int)>;

	GlfwWindow(int width, int height, const char* title);
	~GlfwWindow();

	GlfwWindow(const GlfwWindow&) = delete;
	GlfwWindow& operator=(const GlfwWindow&) = delete;

	[[nodiscard]] bool ShouldClose() const;
	void SwapBuffers() const;

	static void PollEvents();

	void SetMouseButtonHandler(MouseButtonHandler handler);
	void SetCursorPositionHandler(CursorPositionHandler handler);
	void SetFramebufferSizeHandler(FramebufferSizeHandler handler);
	[[nodiscard]] int GetFramebufferWidth() const;
	[[nodiscard]] int GetFramebufferHeight() const;

private:
	void SetupCallbacks();

	static void MouseButtonCallback(GLFWwindow*, int, int, int);
	static void CursorPositionCallback(GLFWwindow*, double, double);
	static void FramebufferSizeCallback(GLFWwindow*, int, int);

	GLFWwindow* m_window = nullptr;

	int m_framebufferWidth = 0;
	int m_framebufferHeight = 0;
	MouseButtonHandler m_mouseButtonHandler;
	CursorPositionHandler m_cursorPositionHandler;
	FramebufferSizeHandler m_framebufferSizeHandler;
};
