#include "Switch.h"
#include "Tile.h"

Switch::Switch(int switchId, float x, float y, Game* game)
	: Actor("res/switch.png", x, y, TILE_WIDTH, TILE_HEIGHT, game)
{
	this->switchId = switchId;
}

void Switch::flick() {
	this->active = !this->active;
}