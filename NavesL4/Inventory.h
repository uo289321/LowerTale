#pragma once
#include "NavegationMenu.h"
class Inventory : public NavegationMenu
{
	Inventory(float x, float y, int width, int height, list<Text*> items, Game* game);
	void select() override;
};

