#include "Polyhedron.h"
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <random>

void Polyhedron::SetData(const std::vector<glm::vec3>& vertices,
	const std::vector<std::vector<size_t>>& facesIndices)
{
	m_vertices = vertices;
	m_faces.clear();

	for (const auto& indices : facesIndices)
	{
		Face face;
		face.vertexIndices = indices;
		face.normal = CalculateNormal(indices);
		m_faces.push_back(face);
	}
}

void Polyhedron::SetRandomColors()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution dis(0, 255);

	for (auto& face : m_faces)
	{
		face.color.r = static_cast<uint8_t>(dis(gen));
		face.color.g = static_cast<uint8_t>(dis(gen));
		face.color.b = static_cast<uint8_t>(dis(gen));
		face.color.a = 128;
	}
}

void Polyhedron::Draw() const
{
	glDepthMask(GL_TRUE);
	glColor3f(0, 0, 0);
	DrawEdges();
	glDepthMask(GL_FALSE);

	glEnable(GL_CULL_FACE);

	glCullFace(GL_FRONT);
	DrawFaces();

	glCullFace(GL_BACK);
	DrawFaces();
	glDepthMask(GL_TRUE);
}

glm::vec3 Polyhedron::CalculateNormal(const std::vector<size_t>& indices) const
{
	if (indices.size() < 3)
	{
		return {0.0f, 0.0f, 1.0f};
	}

	const glm::vec3 v1 = m_vertices[indices[1]] - m_vertices[indices[0]];
	const glm::vec3 v2 = m_vertices[indices[2]] - m_vertices[indices[0]];
	return glm::normalize(glm::cross(v1, v2));
}

void Polyhedron::DrawFaces() const
{
	for (const auto& face : m_faces)
	{
		glBegin(GL_POLYGON);
		glNormal3fv(glm::value_ptr(face.normal));
		glColor4ubv(glm::value_ptr(face.color));
		for (const size_t index : face.vertexIndices)
		{
			glVertex3fv(glm::value_ptr(m_vertices[index]));
		}
		glEnd();
	}
}

void Polyhedron::DrawEdges() const
{
	for (const auto& face : m_faces)
	{
		glBegin(GL_LINE_LOOP);
		for (const size_t index : face.vertexIndices)
		{
			glVertex3fv(glm::value_ptr(m_vertices[index]));
		}
		glEnd();
	}
}