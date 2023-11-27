#pragma once

#include "Actor.h"


class Projectile : public Actor
{
public:
	Projectile(string filename, int origin, float x, float y, int width, int height, Game* game);
	void update();
};

