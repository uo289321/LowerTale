#include "Enemy.h"

Enemy::Enemy(string filename, float x, float y, Game* game)
	: Actor("res/" + filename, x, y, 36, 40, game) {

}

void Enemy::update() {
	// Actualizar la animaci�n
	animation->update();

	vx = -1;
	x = x + vx;

}

void Enemy::draw(float scrollX, float scrollY) {
	Actor::draw();
}

