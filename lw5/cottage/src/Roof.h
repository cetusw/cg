#pragma once

class Roof
{
public:
    Roof(float width, float depth, float height);

    void draw() const;

private:
    float m_width;
    float m_depth;
    float m_height;
};