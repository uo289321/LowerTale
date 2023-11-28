#include "PressurePlate.h"


PressurePlate::PressurePlate(float x, float y, Game* game)
	: Actor("res/pressure_plate.png", x, y, TILE_WIDTH, TILE_HEIGHT, game) {
}

bool PressurePlate::isPressed(list<Box*> boxes) {
	for (Box* box : boxes) {
		if (containsPoint(box->x, box->y)) {
			return true;
		}
	}
	return false;
}



