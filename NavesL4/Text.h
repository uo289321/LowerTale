#pragma once

#include "Game.h"

class Text
{
public:
	Text(string content, float x, float y, Game* game);
	void draw();
	void highlight();
	void unhighlight();
	void hide();
	void show();
	string content; // texto
	int x;
	int y;
	int r, g, b, a;
	int width;
	int height;
	Game* game; // referencia al juego

};

