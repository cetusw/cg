#pragma once

#include "Face.h"

#include <glm/vec3.hpp>
#include <random>
#include <unordered_set>

#include <vector>

class Mesh
{
public:
	Mesh(std::vector<glm::vec3> vertices, std::vector<Face> faces);

	void CalculateNormals();
	void AssignFaceColors();

	[[nodiscard]] const std::vector<glm::vec3>& GetVertices() const;
	[[nodiscard]] const std::vector<Face>& GetFaces() const;

private:
	void ValidateGeometry() const;
	void ValidateFace(const Face& face) const;
	[[nodiscard]] static glm::vec3 CreateFaceColor(
		std::uniform_int_distribution<>& distribution,
		std::unordered_set<uint32_t>& usedColors,
		std::mt19937& random);
	[[nodiscard]] glm::vec3 CalculateNormal(const Face& face) const;

	std::vector<glm::vec3> m_vertices;
	std::vector<Face> m_faces;
};
