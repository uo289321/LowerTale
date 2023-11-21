#pragma once

#include "Actor.h"
#include "Animation.h" 

class Enemy : public Actor
{
public:
	Enemy(float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();
	void receiveDamage(int received);
	void switchToBattle();
	void switchToMoving();


	Animation* aMoving;
	Animation* aCombat;
	Animation* animation; // Referencia a la animación mostrada

	int health = 200;
};
