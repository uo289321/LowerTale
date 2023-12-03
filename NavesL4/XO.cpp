#include "XO.h"

XO::XO(float x, float y, Game* game)
	: Actor("x.png", x, y, TILE_WIDTH, TILE_HEIGHT, game) {
	this->state = 'x';
}

void XO::change() {
	this->state = this->state == 'x' ? 'o' : 'x';
	this->texture = game->getTexture(this->state + ".png");
}
