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
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	void processControls();
	void update() override;
	void draw() override;
	void selectNext();
	void selectPrevious();
	void select();
	void init() override;
	SDL_GameController* gamePad;

	Audio* bgMusic;
	Background* background;
	int selected;
	list<Text*> options;
	int controlMoveX = 0;
	bool controlInteract = false;



};

