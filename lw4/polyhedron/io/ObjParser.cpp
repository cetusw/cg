#include "io/ObjParser.h"

#include <fstream>
#include <stdexcept>
#include <utility>

Mesh ObjParser::Parse(const std::string& filepath)
{
	ObjParser parser;
	return parser.ParseFile(filepath);
}

Mesh ObjParser::ParseFile(const std::string& filepath)
{
	std::ifstream file(filepath);
	if (!file)
	{
		throw std::runtime_error("Failed to open OBJ file: " + filepath);
	}

	std::string line;
	while (std::getline(file, line))
	{
		m_lineNumber++;
		ParseLine(line);
	}
	if (file.bad())
	{
		throw std::runtime_error("Failed to read OBJ file: " + filepath);
	}

	return CreateMesh();
}

void ObjParser::ParseLine(const std::string& line)
{
	std::istringstream input(line);
	std::string recordType;
	if (!(input >> recordType) || recordType == "#")
	{
		return;
	}

	if (recordType == "v")
	{
		ParseVertex(input);
	}
	else if (recordType == "f")
	{
		ParseFace(input);
	}
}

void ObjParser::ParseVertex(std::istringstream& input)
{
	glm::vec3 vertex;
	if (!(input >> vertex.x >> vertex.y >> vertex.z))
	{
		throw std::runtime_error(
			"OBJ line " + std::to_string(m_lineNumber) + ": invalid vertex");
	}
	m_vertices.push_back(vertex);
}

void ObjParser::ParseFace(std::istringstream& input)
{
	Face face;
	std::string token;
	while (input >> token)
	{
		face.vertexIndices.push_back(ParseVertexIndex(token));
	}
	if (face.vertexIndices.size() < 3)
	{
		throw std::runtime_error(
			"OBJ line " + std::to_string(m_lineNumber) + ": face has fewer than three vertices");
	}

	m_faces.push_back(std::move(face));
}

std::size_t ObjParser::ParseVertexIndex(const std::string& token) const
{
	const std::string value = token.substr(0, token.find('/'));
	if (value.empty())
	{
		throw std::runtime_error(
			"OBJ line " + std::to_string(m_lineNumber) + ": missing vertex index");
	}

	try
	{
		const int index = std::stoi(value);
		if (index == 0)
		{
			throw std::runtime_error("zero index");
		}

		const long resolvedIndex = index > 0
			? static_cast<long>(index - 1)
			: static_cast<long>(m_vertices.size()) + index;
		if (resolvedIndex < 0 || static_cast<std::size_t>(resolvedIndex) >= m_vertices.size())
		{
			throw std::runtime_error("out of range");
		}
		return static_cast<std::size_t>(resolvedIndex);
	}
	catch (const std::exception&)
	{
		throw std::runtime_error(
			"OBJ line " + std::to_string(m_lineNumber) + ": invalid vertex index '" + value + "'");
	}
}

Mesh ObjParser::CreateMesh()
{
	Mesh mesh(std::move(m_vertices), std::move(m_faces));
	mesh.CalculateNormals();
	mesh.AssignFaceColors();
	return mesh;
}
