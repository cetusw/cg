#include "Roof.h"

#include <GL/glew.h>

Roof::Roof(
    const float width,
    const float depth,
    const float height
)
    : m_width(width)
    , m_depth(depth)
    , m_height(height)
{
}

void Roof::draw() const
{
    const float halfWidth = m_width / 2.0f;
    const float halfDepth = m_depth / 2.0f;

    constexpr float bottom = 0.0f;
    const float top = m_height;

    glBegin(GL_TRIANGLES);

    // Задний фронтон
    glColor3f(0.5f, 0.15f, 0.1f);

    glVertex3f(-halfWidth, -halfDepth, bottom);
    glVertex3f( halfWidth, -halfDepth, bottom);
    glVertex3f(0.0f,       -halfDepth, top);

    // Передний фронтон
    glColor3f(0.45f, 0.12f, 0.08f);

    glVertex3f( halfWidth, halfDepth, 0.0f);
    glVertex3f(-halfWidth, halfDepth, 0.0f);
    glVertex3f(0.0f,       halfDepth, top);

    glEnd();

    glBegin(GL_QUADS);

    // Левая плоскость крыши
    glColor3f(0.35f, 0.08f, 0.05f);

    glVertex3f(-halfWidth, -halfDepth, 0.0f);
    glVertex3f(0.0f,       -halfDepth, top);
    glVertex3f(0.0f,        halfDepth, top);
    glVertex3f(-halfWidth,  halfDepth, 0.0f);

    // Правая плоскость крыши
    glColor3f(0.4f, 0.1f, 0.06f);

    glVertex3f(0.0f,       -halfDepth, top);
    glVertex3f( halfWidth, -halfDepth, 0.0f);
    glVertex3f( halfWidth,  halfDepth, 0.0f);
    glVertex3f(0.0f,        halfDepth, top);

    glEnd();
}