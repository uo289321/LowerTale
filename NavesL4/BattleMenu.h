#pragma once
#include "Actor.h"
#include <list>
#include "Text.h"
#include "Item.h"
#include "Enemy.h"
#include "Game.h"
#include "GameLayer.h"
class GameLayer;



#define ATTACK 0
#define ITEM 1

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
	int calculateDamage();

	int selected = 0;
	list<Text*> options;
	Text* health;
	Enemy* enemy;
	GameLayer* layer;
	Game* game;
};

