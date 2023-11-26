#pragma once
#include <string>
using namespace std;
#include "Actor.h"
#include "Player.h"
class Player;

class Item : public Actor
{
public:
	Item(string name, float x, float y, int healing, Game* game);
	void use(Player* player);

	string name;
	int healing;
	Game* game;

};

