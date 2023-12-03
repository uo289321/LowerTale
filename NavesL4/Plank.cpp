#include "Plank.h"

Plank::Plank(string filename, float x, float y, Game* game, int orientation) :
	Actor(filename, x, y, 32, 40, game) {

	this->orientation = orientation;
}

void Plank::update() {
	x = x + vx;
	y = y + vy;
}

bool Plank::hasActorNext(Actor* actor) {
	if ((actor->containsPoint(x + (TILE_WIDTH/2.0+1), y) && orientation == game->orientationRight)
		|| (actor->containsPoint(x - (TILE_WIDTH /2.0+1), y) && orientation == game->orientationLeft)
		|| (actor->containsPoint(x, y + (TILE_HEIGHT/2.0+1)) && orientation == game->orientationDown)
		|| (actor->containsPoint(x, y - (TILE_HEIGHT/2.0+1)) && orientation == game->orientationUp)) {
		return true;
	}
	else {
		return false;
	}
}

bool Plank::canMove(list<Tile*> waters, list<Plank*> planks) {
	for (Tile* water : waters) {
		if (hasActorNext(water)) {
			for (Plank* nPlank : planks) {
				if (hasActorNext(nPlank)) {
					return false;
				}
			}
			return true;
		}
	}
	return false;
}


bool Plank::isOnTopOf(Actor* actor) {
	if (actor->containsPoint(x, y)) {
		return true;
	}
	else {
		return false;
	}
}
