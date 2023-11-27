#include "Shield.h"

Shield::Shield(Game* game)
	: Actor("res/shieldX.png", rightX, HEIGHT * 0.5 , SHORT_SIDE, LONG_SIDE, game) {}

void Shield::moveX(int axis) {
	
	this->texture = game->getTexture("res/shieldX.png");
	this->width = SHORT_SIDE;
	this->height = LONG_SIDE;
	this->y = HEIGHT * 0.5;
	if (axis == -1) {
		this->x = leftX;
	}
	else if (axis == 1) {
		this->x = rightX;
	}
}

void Shield::moveY(int axis) {
	this->texture = game->getTexture("res/shieldY.png");
	this->width = LONG_SIDE;
	this->height = SHORT_SIDE;
	this->x = WIDTH * 0.5;

	if (axis == -1) {
		this->y = topY;
	}
	else if (axis == 1) {
		this->y = bottomY;
	}
}
