#include "OBJParser.h"
#include <fstream>
#include <sstream>

Object OBJParser::Parse(const std::string& filepath)
{
	std::ifstream file(filepath);
	if (!file.is_open())
	{
		return {};
	}

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
		{
			continue;
		}

		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "v")
		{

		}
	}
}