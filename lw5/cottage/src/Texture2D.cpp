#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"

#include "Texture2D.h"

#include <iostream>
#include <stdexcept>

namespace
{
    unsigned char *LoadData(
        const std::string &path,
        int &width,
        int &height,
        int &channels)
    {
        unsigned char *data = stbi_load(
            path.c_str(),
            &width,
            &height,
            &channels,
            0 // TODO что такое desired_channels
        );

        if (!data)
        {
            throw std::runtime_error(
                "Failed to load texture: " + path
            );
        }

        return data;
    }

    GLint ValidateFormat(const int channels)
    {
        if (channels == 4)
        {
            return GL_RGBA;
        }
        if (channels == 3)
        {
            return GL_RGB;
        }

        return 0;
    }

    GLuint CreateTexture(
        const GLint format,
        const int width,
        const int height,
        const unsigned char *data)
    {
        GLuint id;
        glGenTextures(
            1,
            &id
        );

        glBindTexture(
            GL_TEXTURE_2D,
            id
        );

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            format,
            width,
            height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            data
        );

        return id;
    }

    void SetParameteri()
    {
        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            GL_REPEAT
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            GL_REPEAT
        );
    }
}

Texture2D::Texture2D(const std::string &path)
{
    int width;
    int height;
    int channels;

    unsigned char *data = LoadData(
        path,
        width,
        height,
        channels
    );

    const GLint format = ValidateFormat(channels);
    if (format == 0)
    {
        stbi_image_free(data);

        throw std::runtime_error(
            "Unsupported texture format: " + path
        );
    }

    m_id = CreateTexture(
        format,
        width,
        height,
        data
    );

    SetParameteri();

    stbi_image_free(data);
}

Texture2D::~Texture2D()
{
    if (m_id != 0)
    {
        glDeleteTextures(1, &m_id);
    }
}

void Texture2D::Bind() const
{
    glBindTexture(
        GL_TEXTURE_2D,
        m_id
    );
}

GLuint Texture2D::GetId() const
{
    return m_id;
}
