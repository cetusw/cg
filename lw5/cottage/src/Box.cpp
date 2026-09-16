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
    glVertex3f(-halfWidth, -halfDepth, bottom);
    glVertex3f( halfWidth, -halfDepth, bottom);
    glVertex3f( halfWidth, -halfDepth, top);
    glVertex3f(-halfWidth, -halfDepth, top);

    // Передняя грань
    glVertex3f( halfWidth, halfDepth, bottom);
    glVertex3f(-halfWidth, halfDepth, bottom);
    glVertex3f(-halfWidth, halfDepth, top);
    glVertex3f( halfWidth, halfDepth, top);

    // Правая грань
    glVertex3f(-halfWidth,  halfDepth, bottom);
    glVertex3f(-halfWidth, -halfDepth, bottom);
    glVertex3f(-halfWidth, -halfDepth, top);
    glVertex3f(-halfWidth,  halfDepth, top);

    // Левая грань
    glVertex3f(halfWidth, -halfDepth, bottom);
    glVertex3f(halfWidth,  halfDepth, bottom);
    glVertex3f(halfWidth,  halfDepth, top);
    glVertex3f(halfWidth, -halfDepth, top);

    // Верх
    glVertex3f(-halfWidth, -halfDepth, top);
    glVertex3f( halfWidth, -halfDepth, top);
    glVertex3f( halfWidth,  halfDepth, top);
    glVertex3f(-halfWidth,  halfDepth, top);

    // Низ
    glVertex3f(-halfWidth,  halfDepth, bottom);
    glVertex3f( halfWidth,  halfDepth, bottom);
    glVertex3f( halfWidth, -halfDepth, bottom);
    glVertex3f(-halfWidth, -halfDepth, bottom);

    glEnd();
}