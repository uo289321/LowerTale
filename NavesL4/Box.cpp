#include "Box.h"

Box::Box(float x, float y, Game* game) :
	Actor("res/caja.png", x, y, 32, 40, game) {
	possibleMovementX = 4;
	possibleMovementY = 4;
}

void Box::update() {
	x = x + vx;
	y = y + vy;
}



