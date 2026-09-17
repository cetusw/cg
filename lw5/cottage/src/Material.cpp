#include "Material.h"

Material::Material(
    const GLfloat ambientR,
    const GLfloat ambientG,
    const GLfloat ambientB,

    const GLfloat diffuseR,
    const GLfloat diffuseG,
    const GLfloat diffuseB,

    const GLfloat specularR,
    const GLfloat specularG,
    const GLfloat specularB,

    const GLfloat shininess
)
    : m_ambient{
          ambientR,
          ambientG,
          ambientB,
          1.0f
      }
      , m_diffuse{
          diffuseR,
          diffuseG,
          diffuseB,
          1.0f
      }
      , m_specular{
          specularR,
          specularG,
          specularB,
          1.0f
      }
      , m_shininess(shininess)
{
}

void Material::Apply() const
{
    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_AMBIENT,
        m_ambient
    );

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_DIFFUSE,
        m_diffuse
    );

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_SPECULAR,
        m_specular
    );

    glMaterialf(
        GL_FRONT_AND_BACK,
        GL_SHININESS,
        m_shininess
    );
}
