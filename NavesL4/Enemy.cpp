#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/enemigo.png", x, y, 36, 40, game) {
	this->aMoving = new Animation("res/enemigo_movimiento.png", 36, 40, 108, 40, 6, 3, true, game);
	this->aCombat = new Animation("res/enemigo.png", 36, 40, 108, 40, 6, 1, true, game);
	animation = aMoving;
	vx = 0;
}

void Enemy::update() {
	// Actualizar la animación
	animation->update();

}

void Enemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

void Enemy::receiveDamage(int dmg) {
	this->health -= dmg;
}

void Enemy::switchToBattle() {
	this->animation = aCombat;
}

void Enemy::switchToMoving() {
	this->animation = aMoving;
}

