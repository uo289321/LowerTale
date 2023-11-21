#pragma once

#include "Actor.h"
#include "Animation.h" 

class Enemy : public Actor
{
public:
	Enemy(string filename, float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();
	void damage(int received);
	void switchProfile();
	Animation* aBattle;
	Animation* animation; // Referencia a la animación mostrada

	int health;
	string animationName;
	string spriteName;
	bool battle = false;
};
