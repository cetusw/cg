#include "Roof.h"

#include <GL/glew.h>

#include "Vec3.h"

Roof::Roof(
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

void Roof::draw() const
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

    glBegin(GL_TRIANGLES);

    // Передний фронтон
    glNormal3f(0.0f, 1.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(halfWidth, halfDepth, 0.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-halfWidth, halfDepth, 0.0f);

    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(0.0f, halfDepth, top);

    // Задний фронтон
    glNormal3f(0.0f, -1.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-halfWidth, -halfDepth, bottom);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(halfWidth, -halfDepth, bottom);

    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(0.0f, -halfDepth, top);

    glEnd();

    glBegin(GL_QUADS);

    // Левая плоскость крыши
    const Vec3 a{
        -halfWidth,
        -halfDepth,
        0.0f
    };

    const Vec3 b{
        0.0f,
        -halfDepth,
        m_height
    };

    const Vec3 c{
        0.0f,
        halfDepth,
        m_height
    };

    const Vec3 leftNormal = CalculateNormal(a, b, c);

    glNormal3f(
        leftNormal.x,
        leftNormal.y,
        leftNormal.z
    );

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-halfWidth, -halfDepth, 0.0f);

    glTexCoord2f(0.0f, repeatZ);
    glVertex3f(0.0f, -halfDepth, top);

    glTexCoord2f(repeatY, repeatZ);
    glVertex3f(0.0f, halfDepth, top);

    glTexCoord2f(repeatY, 0.0f);
    glVertex3f(-halfWidth, halfDepth, 0.0f);

    // Правая плоскость крыши
    const Vec3 d{
        0.0f, -halfDepth, top
    };

    const Vec3 e{
        halfWidth, -halfDepth, 0.0f
    };

    const Vec3 f{
        halfWidth, halfDepth, 0.0f
    };

    const Vec3 rightNormal = CalculateNormal(d, e, f);

    glNormal3f(
        rightNormal.x,
        rightNormal.y,
        rightNormal.z
    );

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, -halfDepth, top);

    glTexCoord2f(0.0f, repeatZ);
    glVertex3f(halfWidth, -halfDepth, 0.0f);

    glTexCoord2f(repeatY, repeatZ);
    glVertex3f(halfWidth, halfDepth, 0.0f);

    glTexCoord2f(repeatY, 0.0f);
    glVertex3f(0.0f, halfDepth, top);

    glEnd();
}
