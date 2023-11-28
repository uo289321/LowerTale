#pragma once
#include "Actor.h"
#include "Tile.h"
#include "Box.h"
#include <list>

class PressurePlate : public Actor
{
public:
	PressurePlate(float x, float y, Game* game);

	bool isPressed(list<Box*> boxes);
	bool is_pressed = false;
};

