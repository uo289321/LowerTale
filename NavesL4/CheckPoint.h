#pragma once
#include "Actor.h"
#include "Tile.h"

class CheckPoint : public Actor
{
public:
	CheckPoint(float x, float y, Game* game);
};
