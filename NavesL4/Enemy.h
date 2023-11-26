#pragma once

#include "Actor.h"
#include "Animation.h" 
#include "GameLayer.h"
class GameLayer;

class Enemy : public Actor
{
public:
	Enemy(string fileName, float x, float y, GameLayer* layer, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();
	GameLayer* layer;
	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada
};
