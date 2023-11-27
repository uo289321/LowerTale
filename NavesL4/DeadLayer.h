#pragma once
#include "Layer.h"
#include <list>
#include "Text.h"

class DeadLayer : public Layer
{
public:
	DeadLayer(Game* game);
	void keysToControls(SDL_Event event);
	void processControls();
	void update() override;
	void draw() override;

	list<Text*> options;
	int controlMoveY;


};

