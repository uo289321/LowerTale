#pragma once

#include "Game.h"

class AnimatedText
{
public:
	AnimatedText(string content, float x, float y, Game* game);
	void draw();
	bool update();
	string content; // texto
	string shown;
	int x;
	int y;
	int width;
	int height;
	int n = 1;
	Game* game; // referencia al juego
};