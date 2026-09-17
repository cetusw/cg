#pragma once

#include <GL/glew.h>

class Material
{
public:
    Material(
        GLfloat ambientR,
        GLfloat ambientG,
        GLfloat ambientB,

        GLfloat diffuseR,
        GLfloat diffuseG,
        GLfloat diffuseB,

        GLfloat specularR,
        GLfloat specularG,
        GLfloat specularB,

        GLfloat shininess
    );

    void Apply() const;

private:
    GLfloat m_ambient[4];
    GLfloat m_diffuse[4];
    GLfloat m_specular[4];

    GLfloat m_shininess;
};
