#include "Box.h"

#include <GL/glew.h>

Box::Box(
    const float width,
    const float depth,
    const float height
)
    : m_width(width)
    , m_depth(depth)
    , m_height(height)
{
}

void Box::draw() const
{
    const float halfWidth = m_width / 2.0f;
    const float halfDepth = m_depth / 2.0f;

    constexpr float bottom = 0.0f;
    const float top = m_height;

    glBegin(GL_QUADS);

    // Задняя грань
    glColor3f(0.8f, 0.3f, 0.2f);

    glVertex3f(-halfWidth, -halfDepth, bottom);
    glVertex3f( halfWidth, -halfDepth, bottom);
    glVertex3f( halfWidth, -halfDepth, top);
    glVertex3f(-halfWidth, -halfDepth, top);

    // Передняя грань
    glColor3f(0.6f, 0.2f, 0.2f);

    glVertex3f( halfWidth, halfDepth, bottom);
    glVertex3f(-halfWidth, halfDepth, bottom);
    glVertex3f(-halfWidth, halfDepth, top);
    glVertex3f( halfWidth, halfDepth, top);

    // Правая грань
    glColor3f(0.7f, 0.25f, 0.2f);

    glVertex3f(-halfWidth,  halfDepth, bottom);
    glVertex3f(-halfWidth, -halfDepth, bottom);
    glVertex3f(-halfWidth, -halfDepth, top);
    glVertex3f(-halfWidth,  halfDepth, top);

    // Левая грань
    glColor3f(0.9f, 0.35f, 0.2f);

    glVertex3f(halfWidth, -halfDepth, bottom);
    glVertex3f(halfWidth,  halfDepth, bottom);
    glVertex3f(halfWidth,  halfDepth, top);
    glVertex3f(halfWidth, -halfDepth, top);

    // Верх
    glColor3f(0.7f, 0.4f, 0.3f);

    glVertex3f(-halfWidth, -halfDepth, top);
    glVertex3f( halfWidth, -halfDepth, top);
    glVertex3f( halfWidth,  halfDepth, top);
    glVertex3f(-halfWidth,  halfDepth, top);

    // Низ
    glColor3f(0.4f, 0.4f, 0.4f);

    glVertex3f(-halfWidth,  halfDepth, bottom);
    glVertex3f( halfWidth,  halfDepth, bottom);
    glVertex3f( halfWidth, -halfDepth, bottom);
    glVertex3f(-halfWidth, -halfDepth, bottom);

    glEnd();
}