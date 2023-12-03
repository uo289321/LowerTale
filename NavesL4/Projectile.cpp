#include "Projectile.h"

Projectile::Projectile(string filename, int origin, float x, float y, int width, int height, Game* game) :
	Actor(filename, x, y, width, height, game) {
	switch (origin) {
	case 0:
		vx = 0;
		vy = 5;
		break;
	case 1:
		vx = -5;
		vy = 0;
		break;
	case 2:
		vx = 0;
		vy = -5;
		break;
	case 3:
		vx = 5;
		vy = 0;
		break;
	}

}

void Projectile::update() {
	x = x + vx;
	y = y + vy;
}
