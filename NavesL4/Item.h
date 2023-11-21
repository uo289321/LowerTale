#pragma once
#include "Actor.h"
class Item : public Actor
{
public:
	Item(string fileName, string name, float x, float y, Game* game);
	string name;
};

