#include "Door.h"

Door::Door(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, TILE_WIDTH, TILE_HEIGHT, game) {
}
