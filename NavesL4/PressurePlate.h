#pragma once
#include "Actor.h"
#include "Tile.h"

class PressurePlate : public Actor
{
public:
	PressurePlate(float x, float y, Game* game);

	bool is_pressed = false;
};

