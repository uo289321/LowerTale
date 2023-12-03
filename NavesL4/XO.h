#pragma once
#include "Actor.h"
#include "Tile.h"
class XO : public Actor
{
public:
	XO(float x, float y, Game* game);
	void change();
	bool playerStanding = false;


	char state = 'x';
};

