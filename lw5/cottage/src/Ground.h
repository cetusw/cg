#pragma once

class Ground
{
public:
    Ground(
        float width,
        float depth,
        float textureScale = 1.0f
    );

    void Draw() const;

private:
    float m_width;
    float m_depth;
    float m_textureScale;
};