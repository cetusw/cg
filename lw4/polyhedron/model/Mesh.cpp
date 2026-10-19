#include "model/Mesh.h"

#include <glm/common.hpp>
#include <glm/geometric.hpp>

#include <algorithm>
#include <cmath>
#include <random>
#include <stdexcept>
#include <unordered_set>
#include <utility>

namespace
{
constexpr float MinNormalLength = 1e-12f;
constexpr std::size_t MinFaceVertexCount = 3;
} // namespace

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<Face> faces)
	: m_vertices(std::move(vertices))
	, m_faces(std::move(faces))
{
	ValidateGeometry();
}

void Mesh::CalculateNormals()
{
	for (Face& face : m_faces)
	{
		face.normal = CalculateNormal(face);
	}
}

void Mesh::AssignFaceColors()
{
	std::mt19937 random(std::random_device{}());
	std::uniform_int_distribution distribution(50, 220);

	std::unordered_set<std::uint32_t> usedColors;

	for (auto & m_face : m_faces)
	{
		m_face.color = CreateFaceColor(distribution, usedColors, random);
	}
}

const std::vector<glm::vec3>& Mesh::GetVertices() const
{
	return m_vertices;
}

const std::vector<Face>& Mesh::GetFaces() const
{
	return m_faces;
}

void Mesh::ValidateGeometry() const
{
	if (m_vertices.empty() || m_faces.empty())
	{
		throw std::runtime_error("OBJ model must contain vertices and faces");
	}

	for (const Face& face : m_faces)
	{
		ValidateFace(face);
	}
}

void Mesh::ValidateFace(const Face& face) const
{
	if (face.vertexIndices.size() < MinFaceVertexCount)
	{
		throw std::runtime_error("OBJ face must contain at least three vertices");
	}

	for (const std::size_t index : face.vertexIndices)
	{
		if (index >= m_vertices.size())
		{
			throw std::runtime_error("OBJ face references a missing vertex");
		}
	}
}

glm::vec3 Mesh::CreateFaceColor(
	std::uniform_int_distribution<>& distribution,
	std::unordered_set<std::uint32_t>& usedColors,
	std::mt19937& random)
{
	int r, g, b;
	std::uint32_t color;

	do
	{
		r = distribution(random);
		g = distribution(random);
		b = distribution(random);

		color = (r << 16) | (g << 8) | b;
	} while (!usedColors.insert(color).second);

	return {
		static_cast<float>(r) / 255.0f,
		static_cast<float>(g) / 255.0f,
		static_cast<float>(b) / 255.0f
	};
}

glm::vec3 Mesh::CalculateNormal(const Face& face) const
{
	const glm::vec3& origin = m_vertices[face.vertexIndices.front()];
	for (std::size_t index = 1; index + 1 < face.vertexIndices.size(); ++index)
	{
		const glm::vec3 normal = glm::cross(
			m_vertices[face.vertexIndices[index]] - origin,
			m_vertices[face.vertexIndices[index + 1]] - origin);
		if (glm::dot(normal, normal) > MinNormalLength)
		{
			return glm::normalize(normal);
		}
	}
	throw std::runtime_error("OBJ model contains a degenerate face");
}
