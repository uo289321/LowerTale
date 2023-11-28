#pragma once
#include "Layer.h"
#include <list>
#include "Text.h"
#include "GameLayer.h"

class DeadLayer : public Layer
{
public:
	DeadLayer(Game* game);
	void keysToControls(SDL_Event event);
	void processControls();
	void update() override;
	void draw() override;
	void selectNext();
	void selectPrevious();
	void select();


	int selected;
	list<Text*> options;
	int controlMoveX;
	bool controlInteract;



};

