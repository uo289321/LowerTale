#pragma once
#include "Actor.h"

class Switch : public Actor {
public:
	Switch(int switchId, float x, float y, Game* game);
	void flick();

	int switchId;
	bool active = false;
};