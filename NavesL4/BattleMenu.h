#pragma once
#include "Actor.h"
#include <list>
#include "Text.h"
class BattleMenu : public Actor
{
public:
	BattleMenu();
	void selectNext();
	void selectPrevious();
	void select();
	void draw(float scrollX = 0, float scrollY = 0) override;
	void init();
	void update(int health);
	void hideOptions();
	void showOptions();

	int selected;
	list<Text*> options;
	Text* health;
};

