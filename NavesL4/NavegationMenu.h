#pragma once
#include "Actor.h"
#include "Text.h"
#include <list>

class NavegationMenu : public Actor
{
public:
	NavegationMenu(float x, float y, int width, int height, list<Text*> options, Game* game);
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	virtual void select();

	void draw(float scrollX = 0, float scrollY = 0) override;

	list<Text*> options;

	int selected;
	int width;

};

