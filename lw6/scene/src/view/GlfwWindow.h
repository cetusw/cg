#pragma once

#include <functional>
#include <glm/glm.hpp>

struct GLFWwindow;

class GlfwWindow
{
public:
	using MouseButtonHandler = std::function<void(int button, int action, glm::dvec2 mousePosition)>;
	using CursorPositionHandler = std::function<void(glm::dvec2 mousePosition)>;
	using FramebufferSizeHandler = std::function<void(int width, int height)>;

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
	static void InitializeGlfw();
	void CreateWindow(int width, int height, const char* title);
	void InitializeOpenGL() const;
	void SetupCallbacks() const;
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void CursorPositionCallback(GLFWwindow* window, double x, double y);
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* m_window = nullptr;
	int m_framebufferWidth = 0;
	int m_framebufferHeight = 0;
	MouseButtonHandler m_mouseButtonHandler;
	CursorPositionHandler m_cursorPositionHandler;
	FramebufferSizeHandler m_framebufferSizeHandler;
};
