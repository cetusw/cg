#include "Ground.h"

#include <GL/glew.h>

Ground::Ground(
    const float width,
    const float depth,
    const float textureScale
)
    : m_width(width)
    , m_depth(depth)
    , m_textureScale(textureScale)
{
}

void Ground::Draw() const
{
    const float halfWidth = m_width / 2.0f;
    const float halfDepth = m_depth / 2.0f;

    const float repeatX =
        m_width / m_textureScale;

    const float repeatY =
        m_depth / m_textureScale;

    glBegin(GL_QUADS);

    glNormal3f(
        0.0f,
        0.0f,
        1.0f
    );

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(
        -halfWidth,
        -halfDepth,
        0.0f
    );

    glTexCoord2f(repeatX, 0.0f);
    glVertex3f(
        halfWidth,
        -halfDepth,
        0.0f
    );

    glTexCoord2f(repeatX, repeatY);
    glVertex3f(
        halfWidth,
        halfDepth,
        0.0f
    );

    glTexCoord2f(0.0f, repeatY);
    glVertex3f(
        -halfWidth,
        halfDepth,
        0.0f
    );

    glEnd();
}