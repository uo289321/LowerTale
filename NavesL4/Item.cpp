#include "Item.h"
Item::Item(string fileName, string name, float x, float y, Game* game)
	: Actor(fileName, x, y, WIDTH, HEIGHT, game) {
	this->name = name;
}
