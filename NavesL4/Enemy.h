#pragma once

#include "Actor.h"
#include "Animation.h" 
#include "GameLayer.h"
class GameLayer;

class Enemy : public Actor
{
public:
	Enemy(string fileName, int fireRate, float x, float y, GameLayer* layer, Game* game);
	void drawAnim(); // Va a sobrescribir
	Projectile* update();
	Projectile* generateProjectile();

	int fireRate;
	int counter;
	GameLayer* layer;
	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada
};
