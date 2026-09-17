#pragma once

class Roof
{
public:
    Roof(
        float width,
        float depth,
        float height,
        float textureScale = 1.0f
    );

    void draw() const;

private:
    float m_width;
    float m_depth;
    float m_height;

    float m_textureScale;
};
