#include "Box.h"

#include <GL/glew.h>

Box::Box(
    const float width,
    const float depth,
    const float height,
    const float textureScale
)
    : m_width(width)
      , m_depth(depth)
      , m_height(height)
      , m_textureScale(textureScale)

{
}

void Box::draw() const
{
    const float halfWidth = m_width / 2.0f;
    const float halfDepth = m_depth / 2.0f;

    constexpr float bottom = 0.0f;
    const float top = m_height;

    const float repeatX =
            m_width / m_textureScale;

    const float repeatY =
            m_depth / m_textureScale;

    const float repeatZ =
            m_height / m_textureScale;

    glBegin(GL_QUADS);

    // Передняя грань
    glNormal3f(0.0f, 1.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(halfWidth, halfDepth, bottom);

    glTexCoord2f(repeatX, 0.0f);
    glVertex3f(-halfWidth, halfDepth, bottom);

    glTexCoord2f(repeatX, repeatZ);
    glVertex3f(-halfWidth, halfDepth, top);

    glTexCoord2f(0.0f, repeatZ);
    glVertex3f(halfWidth, halfDepth, top);

    // Задняя грань
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-halfWidth, -halfDepth, bottom);

    glTexCoord2f(repeatX, 0.0f);
    glVertex3f(halfWidth, -halfDepth, bottom);

    glTexCoord2f(repeatX, repeatZ);
    glVertex3f(halfWidth, -halfDepth, top);

    glTexCoord2f(0.0f, repeatZ);
    glVertex3f(-halfWidth, -halfDepth, top);

    // Левая грань
    glNormal3f(-1.0f, 0.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(halfWidth, -halfDepth, bottom);

    glTexCoord2f(repeatY, 0.0f);
    glVertex3f(halfWidth, halfDepth, bottom);

    glTexCoord2f(repeatY, repeatZ);
    glVertex3f(halfWidth, halfDepth, top);

    glTexCoord2f(0.0f, repeatZ);
    glVertex3f(halfWidth, -halfDepth, top);

    // Правая грань
    glNormal3f(1.0f, 0.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-halfWidth, halfDepth, bottom);

    glTexCoord2f(repeatY, 0.0f);
    glVertex3f(-halfWidth, -halfDepth, bottom);

    glTexCoord2f(repeatY, repeatZ);
    glVertex3f(-halfWidth, -halfDepth, top);

    glTexCoord2f(0.0f, repeatZ);
    glVertex3f(-halfWidth, halfDepth, top);

    // Верх
    glNormal3f(0.0f, 0.0f, 1.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-halfWidth, -halfDepth, top);

    glTexCoord2f(repeatX, 0.0f);
    glVertex3f(halfWidth, -halfDepth, top);

    glTexCoord2f(repeatX, repeatY);
    glVertex3f(halfWidth, halfDepth, top);

    glTexCoord2f(0.0f, repeatY);
    glVertex3f(-halfWidth, halfDepth, top);

    // Низ
    glNormal3f(0.0f, 0.0f, -1.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-halfWidth, halfDepth, bottom);

    glTexCoord2f(repeatX, 0.0f);
    glVertex3f(halfWidth, halfDepth, bottom);

    glTexCoord2f(repeatX, repeatY);
    glVertex3f(halfWidth, -halfDepth, bottom);

    glTexCoord2f(0.0f, repeatY);
    glVertex3f(-halfWidth, -halfDepth, bottom);

    glEnd();
}
