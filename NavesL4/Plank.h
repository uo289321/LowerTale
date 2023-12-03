#pragma once
#include "Actor.h"
#include "Tile.h"
#include <list>

class Plank :
    public Actor
{
public:
	Plank(string fileName, float x, float y, Game* game, int orientation);
	void update();
	bool hasActorNext(Actor* actor);
	bool isOnTopOf(Actor* actor);
	bool canMove(list<Tile*> waters, list<Plank*> planks);
	int orientation;
};

