#define GLFW_INCLUDE_NONE

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebufferSizeCallback(
    GLFWwindow*,
    const int width,
    const int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(
        800,
        600,
        "Cottage",
        nullptr,
        nullptr
    );

    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";

        glfwDestroyWindow(window);
        glfwTerminate();

        return 1;
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glEnable(GL_DEPTH_TEST);

    glClearColor(
        0.2f,
        0.3f,
        0.4f,
        1.0f
    );

    while (!glfwWindowShouldClose(window))
    {
        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}