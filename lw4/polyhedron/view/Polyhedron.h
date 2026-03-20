#pragma once
#include "../model/Face.h"
#include <glm/glm.hpp>
#include <vector>

class Polyhedron
{
public:
	Polyhedron() = default;

	void SetData(const std::vector<glm::vec3>& vertices, const std::vector<std::vector<size_t>>& facesIndices);
	void SetRandomColors();
	void Draw() const;

private:
	std::vector<glm::vec3> m_vertices{};
	std::vector<Face> m_faces{};

	[[nodiscard]] glm::vec3 CalculateNormal(const std::vector<size_t>& indices) const;
	void DrawFaces() const;
	void DrawEdges() const;
};
