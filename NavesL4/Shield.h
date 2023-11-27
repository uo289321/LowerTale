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

	int leftX = WIDTH * 0.48;
	int rightX = WIDTH * 0.52;
	int topY = HEIGHT * 0.48;
	int bottomY = HEIGHT * 0.52;
};

