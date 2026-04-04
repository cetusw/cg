#include "Application.h"
#include <iostream>

int main(const int argc, char* argv[])
{
	if (argc < 4)
	{
		std::cerr << "Usage: " << argv[0] << " NUM_SUPPLIERS NUM_CLIENTS NUM_AUDITORS" << std::endl;
		return 1;
	}

	try
	{
		const int numSuppliers = std::stoi(argv[1]);
		const int numClients = std::stoi(argv[2]);
		const int numAuditors = std::stoi(argv[3]);
		constexpr int capacity = 100;
		Application app(numSuppliers, numClients, numAuditors, capacity);
		app.Run();
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error(e.what());
	}

	return 0;
}