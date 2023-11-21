#pragma once
#include "Actor.h"

class Plank :
    public Actor
{
public:
	Plank(float x, float y, Game* game);
	void update();
};

