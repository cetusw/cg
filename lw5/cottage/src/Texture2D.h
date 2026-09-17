#pragma once

#include <GL/glew.h>

#include <string>

class Texture2D
{
public:
    explicit Texture2D(const std::string& path);

    ~Texture2D();

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    void Bind() const;

    [[nodiscard]] GLuint GetId() const;

private:
    GLuint m_id = 0;
};