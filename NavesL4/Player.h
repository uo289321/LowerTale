#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h"
#include "Tile.h"
#include "Item.h"
#include <list>
class Item;
#include "Plank.h"
#include "Box.h"

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
	bool isTouching(Actor* actor);
	bool canMoveActor(Actor* actor);
	Plank* throwPlank();
	int throwCadence = 5;
	int throwTime = 0;
	void heal(int healing);
	bool hurt(int dmg);
	void pick(Item* item);
	int state;
	int orientation;
	bool moving = false;
	bool hasPlank = false;
	int movingCd = 0;
	Audio* audioShoot;


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

