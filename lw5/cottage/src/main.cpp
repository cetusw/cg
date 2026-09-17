#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Box.h"
#include "Roof.h"

#include <iostream>

GLuint loadTexture(const char *path)
{
    int width;
    int height;
    int channels;

    unsigned char *data = stbi_load(
        path,
        &width,
        &height,
        &channels,
        0
    );

    if (!data)
    {
        std::cerr << "Failed to load texture: "
                << path << '\n';

        return 0;
    }

    GLint format;

    if (channels == 4)
    {
        format = GL_RGBA;
    } else
    {
        format = GL_RGB;
    }

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_REPEAT
    );

    stbi_image_free(data);

    return texture;
}

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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);

    const GLuint brickTexture =
            loadTexture("../assets/brick.jpg");

    glClearColor(
        0.2f,
        0.3f,
        0.4f,
        1.0f
    );

    const Box foundation(7.0f, 5.0f, 0.4f);
    const Box houseBody(6.0f, 4.0f, 3.0f);
    const Box garage(3.0f, 4.0f, 2.5f);
    const Roof roof(6.8f, 4.8f, 1.8f);
    const Box houseWindow(1.0f, 0.08f, 1.2f);
    const Box door(1.2f, 0.10f, 2.2f);

    constexpr GLfloat lightDiffuse[] = {
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };

    constexpr GLfloat lightAmbient[] = {
        0.2f,
        0.2f,
        0.2f,
        1.0f
    };

    constexpr GLfloat lightSpecular[] = {
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    while (!glfwWindowShouldClose(window))
    {
        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(
            5.0, -10.0, 7.0,
            0.0, 0.0, 1.5,
            0.0, 0.0, 1.0
        );

        constexpr GLfloat lightPosition[] = {
            -5.0f,
            -5.0f,
            8.0f,
            1.0f
        };

        glLightfv(
            GL_LIGHT0,
            GL_POSITION,
            lightPosition
        );

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glColor3f(0.35f, 0.35f, 0.35f);
        foundation.draw();
        glPopMatrix();

        constexpr GLfloat wallDiffuse[] = {
            0.75f,
            0.25f,
            0.15f,
            1.0f
        };

        constexpr GLfloat wallAmbient[] = {
            0.3f,
            0.1f,
            0.08f,
            1.0f
        };

        constexpr GLfloat wallSpecular[] = {
            0.1f,
            0.1f,
            0.1f,
            1.0f
        };

        glMaterialfv(
            GL_FRONT_AND_BACK,
            GL_DIFFUSE,
            wallDiffuse
        );

        glMaterialfv(
            GL_FRONT_AND_BACK,
            GL_AMBIENT,
            wallAmbient
        );

        glMaterialfv(
            GL_FRONT_AND_BACK,
            GL_SPECULAR,
            wallSpecular
        );

        glMaterialf(
            GL_FRONT_AND_BACK,
            GL_SHININESS,
            8.0f
        );

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.4f);
        glColor3f(1, 1, 1);
        houseBody.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(5.0f, 0.0f, 0.0f);
        glColor3f(0.75f, 0.25f, 0.15f);
        garage.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 3.4f);
        glColor3f(0.75f, 0.25f, 0.15f);
        roof.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.7f, -2.04f, 1.4f);
        glColor3f(0.2f, 0.5f, 0.8f);
        houseWindow.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.7f, -2.04f, 1.4f);
        glColor3f(0.2f, 0.5f, 0.8f);
        houseWindow.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, -2.05f, 0.4f);
        glColor3f(0.2f, 0.5f, 0.8f);
        door.draw();
        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
