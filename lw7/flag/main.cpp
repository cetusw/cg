#include "controller/Application.h"

#include <exception>
#include <iostream>

int main()
{
	try
	{
		Application application;
		return application.Run();
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Application error: " << exception.what() << '\n';
		return 1;
	}
}
