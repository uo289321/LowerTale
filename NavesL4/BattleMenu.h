#pragma once
#include "Actor.h"
#include <list>
#include "Text.h"
#include "Item.h"
#include "GameLayer.h"
#include "Enemy.h"
class Enemy;
class GameLayer;

#define BLOCK_CD 5

class BattleMenu
{
public:
	BattleMenu(Enemy* enemy, GameLayer* layer, Game* game);
	void selectNext();
	void selectPrevious();
	void select();
	void draw();
	void update();
	void hideOptions();
	void showOptions();
	void blockRight();
	void blockLeft();
	void blockUp();
	void blockDown();


	int blockCd;
	Enemy* enemy;
	int selected;
	list<Text*> options;
	Text* health;
	GameLayer* layer;
	Game* game;
};

