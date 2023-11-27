#include "Box.h"

Box::Box(float x, float y, Game* game) :
	Actor("res/caja.png", x, y, TILE_WIDTH, TILE_HEIGHT, game) {

}

void Box::update() {
	x = x + vx;
	y = y + vy;
}

bool Box::isOnTopOf(Actor* actor) {
	if (actor->containsPoint(x, y)) {
		return true;
	}
	else {
		return false;
	}
}



