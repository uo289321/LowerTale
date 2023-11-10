#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Projectile* shoot();
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void moveTileX(float axis);
	void moveTileY(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	int state;
	int orientation;
	Audio* audioShoot;

	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aIdleUp;
	Animation* aIdleDown;

	Animation* aMovingLeft;
	Animation* aMovingUp;
	Animation* aMovingDown;
	Animation* aMovingRight;

	Animation* animation; // Referencia a la animaci�n mostrada

	int timeTillNextXMove = 0;
	int timeTillNextYMove = 0;
};

