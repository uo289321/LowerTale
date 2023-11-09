#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h"

#define MAX_HP 20

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Projectile* shoot();
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void heal(int amount);

	int hp = MAX_HP;
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

	Animation* animation; // Referencia a la animación mostrada
};

