#pragma once
#include "Actor.h"
#include "Tile.h"

class Door : public Actor
{
public:
	Door(string fileName, float x, float y, Game* game);
	bool is_open = false;
};

