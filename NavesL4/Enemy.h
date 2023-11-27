#pragma once

#include "Actor.h"
#include "Animation.h" 
#include "GameLayer.h"
class GameLayer;

class Enemy : public Actor
{
public:
	Enemy(string fileName, int hp, int damage, int fireRate, float x, float y, Game* game);
	void drawAnim(); // Va a sobrescribir
	Projectile* update();
	Projectile* generateProjectile();
	void restore();
	void receiveDamage(int damage);
	bool isDead();

	int fireRate;
	int counter;
	int damage;
	int maxHp;
	int hp;
	GameLayer* layer;
	Animation* animation; // Referencia a la animación mostrada
};
