#pragma once
#include "Actor.h"
#include <list>
#include "Text.h"
#include "Item.h"
#include "BattleLayer.h"
#include "Enemy.h"
#include "Animation.h"
class Enemy;
class BattleLayer;

#define BLOCK_CD 5
#define DEFENSE_DURATION 600 // 20 segundos (habiendo 30 iteraciones en un segundo)

class BattleMenu
{
public:
	BattleMenu(Enemy* enemy, BattleLayer* layer, Game* game);
	void selectNext();
	void selectPrevious();
	void select();
	void draw();
	void hideOptions();
	void showOptions();
	void blockRight();
	void blockLeft();
	void blockUp();
	void blockDown();

	void attack();

	Animation* slash;
	int blockCd;
	Enemy* enemy;
	int selected;
	list<Text*> options;
	BattleLayer* layer;
	Game* game;
};

