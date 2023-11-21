#include "Plank.h"

Plank::Plank(float x, float y, Game* game) :
	Actor("res/plank.png", x, y, 32, 40, game) {
	vx = 5;
}

void Plank::update() {
	x = x + vx;
}
