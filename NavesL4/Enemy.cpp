#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/enemigo.png", x, y, 36, 40, game) {

}

void Enemy::update() {
	// Actualizar la animación
	animation->update();

	vx = -1;
	x = x + vx;

}

void Enemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

