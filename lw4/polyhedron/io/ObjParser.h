#pragma once

#include "model/Mesh.h"

#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

class ObjParser
{
public:
	[[nodiscard]] static Mesh Parse(const std::string& filepath);

private:
	[[nodiscard]] Mesh ParseFile(const std::string& filepath);
	void ParseLine(const std::string& line);
	void ParseVertex(std::istringstream& input);
	void ParseFace(std::istringstream& input);
	[[nodiscard]] std::size_t ParseVertexIndex(const std::string& token) const;
	[[nodiscard]] Mesh CreateMesh();

	std::vector<glm::vec3> m_vertices;
	std::vector<Face> m_faces;
	std::size_t m_lineNumber = 0;
};
