#include "Tile.h"



Tile::Tile(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, TILE_WIDTH, TILE_HEIGHT, game) {

}
