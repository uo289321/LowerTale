#include "Enemy.h"

Enemy::Enemy(string fileName, float x, float y, Game* game)
	: Actor(fileName, x, y, 36, 40, game) {
	vx = 0;
	this->animation = new Animation(fileName); // insertar resto de par�metros para animaci�n de combate


}

void Enemy::update() {
	// Actualizar la animaci�n
	animation->update();
}

void Enemy::switchProfile() {
	battle = !battle;
}

void Enemy::draw(float scrollX, float scrollY) {
	if (battle)
		animation->draw(x - scrollX, y - scrollY);
	else
		
}

void Enemy::damage(int received) {
	this->health -= received;
}

