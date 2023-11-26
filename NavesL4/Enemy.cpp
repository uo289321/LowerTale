#include "Enemy.h"

Enemy::Enemy(string filename, float x, float y, GameLayer* layer, Game* game)
	: Actor("res/" + filename + ".png", x, y, 36, 40, game) {
	this->layer = layer;
	this->animation = new Animation("res/" + filename + "battle.png", 21, 19, 42, 19, 5, 2, true, game);
}

void Enemy::update() {
	// Actualizar la animación
	if(layer->player->state == game->stateBattle)
		animation->update();
}

void Enemy::draw(float scrollX, float scrollY) {
	if(layer->player->state == game->stateMoving || (layer->lastState == game->stateMoving && layer->player->state != game->stateBattle))
		Actor::draw();
	if (layer->player->state == game->stateBattle || layer->lastState == game->stateBattle)
		animation->draw(WIDTH / 2, HEIGHT / 2);
}

