#pragma once
#include "Actor.h"
#include "Tile.h"

class Plank :
    public Actor
{
public:
	Plank(float x, float y, Game* game, int orientation);
	void update();
	bool hasWaterNext(Tile* water);
	int orientation;
};

