#define GLFW_INCLUDE_NONE

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

void drawCube()
{
    glBegin(GL_QUADS);

    // Передняя грань
    glColor3f(1.0f, 0.0f, 0.0f);

    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Задняя грань
    glColor3f(0.0f, 1.0f, 0.0f);

    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // Левая грань
    glColor3f(0.0f, 0.0f, 1.0f);

    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Правая грань
    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Верхняя грань
    glColor3f(1.0f, 0.0f, 1.0f);

    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Нижняя грань
    glColor3f(0.0f, 1.0f, 1.0f);

    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    glEnd();
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

    while (!glfwWindowShouldClose(window))
    {
        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(
            4.0, -6.0, 4.0,
            0.0, 0.0, 0.0,
            0.0, 0.0, 1.0
        );

        drawCube();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
