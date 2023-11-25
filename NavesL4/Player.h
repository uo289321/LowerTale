#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h"
#include "Tile.h"
#include "Item.h"
#include <list>
class Item;

#define MAX_HEALTH 20

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	bool isInRange(Actor* actor);
	void heal(int healing);
	void pick(Item* item);
	int state;
	int orientation;
	bool moving = false;
	int movingCd = 0;
	Audio* audioShoot;
	int health = 20;

	int health = MAX_HEALTH;

	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aIdleUp;
	Animation* aIdleDown;

	Animation* aMovingLeft;
	Animation* aMovingUp;
	Animation* aMovingDown;
	Animation* aMovingRight;

	Animation* animation; // Referencia a la animación mostrada

	list<Item*> inventory;
};

