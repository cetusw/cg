#define GLFW_INCLUDE_NONE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Box.h"
#include "Roof.h"

#include <iostream>

void setupProjection(const int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }

    const double aspect =
            static_cast<double>(width) /
            static_cast<double>(height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        60.0,
        aspect,
        0.1,
        100.0
    );

    glMatrixMode(GL_MODELVIEW);
}

void framebufferSizeCallback(
    GLFWwindow *,
    const int width,
    const int height)
{
    glViewport(0, 0, width, height);

    setupProjection(width, height);
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

    GLFWwindow *window = glfwCreateWindow(
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

    int width;
    int height;

    glfwGetFramebufferSize(window, &width, &height);

    framebufferSizeCallback(
        window,
        width,
        height
    );

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

    Box foundation(7.0f, 5.0f, 0.4f);
    const Box houseBody(6.0f, 4.0f, 3.0f);
    Box garage(3.0f, 4.0f, 2.5f);
    Roof roof(6.8f, 4.8f, 1.8f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(
            5.0, 10.0, 7.0,
            0.0, 0.0, 1.5,
            0.0, 0.0, 1.0
        );

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        foundation.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.4f);
        houseBody.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(5.0f, 0.0f, 0.0f);
        garage.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 3.4f);
        roof.draw();
        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
