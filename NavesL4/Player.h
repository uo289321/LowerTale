#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h"
#include "Tile.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Projectile* shoot();
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	bool isInRange(Actor* actor);
	int state;
	int orientation;
	Audio* audioShoot;


	int movingCd = 0;

	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aIdleUp;
	Animation* aIdleDown;

	Animation* aMovingLeft;
	Animation* aMovingUp;
	Animation* aMovingDown;
	Animation* aMovingRight;

	Animation* animation; // Referencia a la animación mostrada
};

