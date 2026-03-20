#include "controller/PolyhedronApp.h"
#include <exception>
#include <iostream>

int main()
{
	try
	{
		PolyhedronApp app(800, 600, "Polyhedron Viewer");
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return -1;
	}
	return 0;
}
