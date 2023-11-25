#include "Item.h"
#include "Tile.h"

Item::Item(string name, float x, float y, int healing, Game* game) 
	: Actor("res/" + name + ".png", x, y, TILE_WIDTH, TILE_HEIGHT, game)
{
	this->name = name;
	this->healing = healing;
}

void Item::use(Player* p) {
	p->heal(this->healing);
}


