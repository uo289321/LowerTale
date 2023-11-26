#include "Enemy.h"

Enemy::Enemy(string filename, int fireRate, float x, float y, GameLayer* layer, Game* game)
	: Actor("res/" + filename + ".png", x, y, TILE_WIDTH, TILE_HEIGHT, game) {
	this->layer = layer;
	this->fireRate = fireRate;
	this->animation = new Animation("res/" + filename + "battle.png", 21, 19, 42, 19, 5, 2, true, game);
	this->counter = 0;
}

Projectile* Enemy::update() {
	counter--;

	if (counter <= 0) {
		counter = fireRate;
		return generateProjectile();
	}
			
	return NULL;
}

		


Projectile* Enemy::generateProjectile() {
	int min = 0;
	int max = 3;
	int origin = rand() % (max - min + 1) + min;
	Projectile* p = NULL;
	switch (origin) {
	case 0:
		p = new Projectile("res/disparoY.png", origin, WIDTH / 2, 0, 6, 18, game);
		break;
	case 1:
		p = new Projectile("res/disparoX.png", origin, WIDTH, HEIGHT / 2, 18, 6, game);
		break;
	case 2:
		p = new Projectile("res/disparoY.png", origin, WIDTH / 2, HEIGHT, 6, 18, game);
		break;
	case 3:
		p = new Projectile("res/disparoX.png", origin, 0, HEIGHT / 2, 18, 6, game);
		break;
	}

	return p;
}



void Enemy::drawAnim() {
	animation->draw(WIDTH / 2, HEIGHT / 2);
}

