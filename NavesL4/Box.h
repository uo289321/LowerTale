#pragma once

#include "Actor.h"
#include "Tile.h"
#include <list>
class Box : public Actor
{
public:
	Box(float x, float y, Game* game);
	void update();
};

