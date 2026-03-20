#pragma once
#include <GL/gl.h>
#include <glm/vec3.hpp>

class DirectLight
{
public:
	explicit DirectLight(glm::vec3 const& lightDirection = { 0, 0, 1 });

	void SetDirection(glm::vec3 const& direction);
	void SetDiffuseIntensity(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
	void SetAmbientIntensity(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
	void SetSpecularIntensity(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);

	void SetLight(GLenum light) const;

private:
	glm::vec3 m_direction{};
	GLfloat m_diffuse[4]{};
	GLfloat m_ambient[4]{};
	GLfloat m_specular[4]{};
};
