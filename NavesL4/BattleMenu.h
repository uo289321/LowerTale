#pragma once
#include "Actor.h"
#include <list>
#include "Text.h"
#include "Item.h"
class BattleMenu
{
public:
	BattleMenu(Game* game);
	void selectNext();
	void selectPrevious();
	void select();
	void draw();
	void init();
	void update(int health);
	void hideOptions();
	void showOptions();
	void loadInventory(list<Item*> inventory);

	int selected;
	list<Text*> options;
	Text* health;
};

