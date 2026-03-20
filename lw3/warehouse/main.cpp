#include "Application.h"
#include <iostream>

int main(const int argc, char* argv[])
{
	if (argc < 4)
	{
		std::cerr << "Usage: " << argv[0] << " NUM_SUPPLIERS NUM_CLIENTS NUM_AUDITORS" << std::endl;
		return 1;
	}

	Application app(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]), 100);
	app.Run();

	return 0;
}