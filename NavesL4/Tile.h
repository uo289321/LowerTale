#pragma once
#include "Actor.h"

#define TILE_WIDTH 32
#define TILE_HEIGHT 40

class Tile : public Actor
{
public:
	Tile(string filename, float x, float y, Game* game);
};
    

