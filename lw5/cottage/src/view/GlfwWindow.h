#pragma once

struct GLFWwindow;

class GlfwWindow
{
public:
	GlfwWindow(int width, int height, const char* title);
	~GlfwWindow();

	GlfwWindow(const GlfwWindow&) = delete;
	GlfwWindow& operator=(const GlfwWindow&) = delete;

	[[nodiscard]] bool ShouldClose() const;
	void SwapBuffers() const;

	void PollEvents();

private:
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void SetProjection(int width, int height);

	GLFWwindow* m_window{};
};
