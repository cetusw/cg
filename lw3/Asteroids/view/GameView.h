#pragma once

#include "model/Ship.h"

class GameView
{
public:
	static void DrawShip(const Ship& ship);
	static void Reshape(int width, int height);
};
