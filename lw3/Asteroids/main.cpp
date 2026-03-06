#include "controller/AsteroidsApplication.h"

int main(int argc, char** argv)
{
	AsteroidsApplication app("Asteroids", 1920, 1080);
	app.MainLoop();
	return 0;
}