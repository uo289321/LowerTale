#include "Plank.h"

Plank::Plank(float x, float y, Game* game, int orientation) :
	Actor("res/plankoutline.png", x, y, 32, 40, game) {

	this->orientation = orientation;
}

void Plank::update() {
	x = x + vx;
	y = y + vy;
}

bool Plank::hasWaterNext(Tile* water) {
	if ((water->containsPoint(x + TILE_WIDTH/2, y) && orientation == game->orientationRight)
		|| (water->containsPoint(x - TILE_WIDTH/2, y) && orientation == game->orientationLeft)
		|| (water->containsPoint(x, y + TILE_HEIGHT/2) && orientation == game->orientationDown)
		|| (water->containsPoint(x, y - TILE_HEIGHT/2) && orientation == game->orientationUp)) {
		return true;
	}
	else {
		return false;
	}
}
