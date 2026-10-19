#include "view/MeshRenderer.h"

#include <GL/glew.h>

void MeshRenderer::Draw(const Mesh& mesh)
{
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glPolygonOffset(1.0f, 1.0f);
	glEnable(GL_POLYGON_OFFSET_FILL);
	DrawEdges(mesh);
	glDisable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	DrawFaces(mesh, 0.4f);
	glCullFace(GL_BACK);
	DrawFaces(mesh, 0.4f);
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void MeshRenderer::DrawFaces(const Mesh& mesh, const float alpha)
{
	for (const Face& face : mesh.GetFaces())
	{
		glColor4f(face.color.r, face.color.g, face.color.b, alpha);
		glNormal3f(face.normal.x, face.normal.y, face.normal.z);
		glBegin(GL_POLYGON);
		for (const std::size_t index : face.vertexIndices)
		{
			const glm::vec3& vertex = mesh.GetVertices()[index];
			glVertex3f(vertex.x, vertex.y, vertex.z);
		}
		glEnd();
	}
}

void MeshRenderer::DrawEdges(const Mesh& mesh)
{
	glDisable(GL_LIGHTING);
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1.0f);
	for (const Face& face : mesh.GetFaces())
	{
		glBegin(GL_LINE_LOOP);
		for (const std::size_t index : face.vertexIndices)
		{
			const glm::vec3& vertex = mesh.GetVertices()[index];
			glVertex3f(vertex.x, vertex.y, vertex.z);
		}
		glEnd();
	}
	glEnable(GL_LIGHTING);
}
