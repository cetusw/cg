#include "controller/Application.h"

#include <exception>
#include <iostream>
#include <string>

int main(const int argc, char* argv[])
{
	try
	{
		const std::string modelPath = argc > 1 ? argv[1] : "";
		Application application(modelPath);
		return application.Run();
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Application error: " << exception.what() << '\n';
		return 1;
	}
}
