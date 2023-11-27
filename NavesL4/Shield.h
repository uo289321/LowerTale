#pragma once
#include "Actor.h"

#define LONG_SIDE 30
#define SHORT_SIDE 5
class Shield : public Actor
{
public:
	Shield(Game* game);
	void moveX(int axis);
	void moveY(int axis);

	int leftX = WIDTH / 2 - WIDTH * 0.05;
	int rightX = WIDTH / 2 + WIDTH * 0.05;
	int topY = HEIGHT / 2 - WIDTH * 0.05;
	int bottomY = HEIGHT / 2 + WIDTH * 0.05;
};

