#pragma once

#include "Game.h"

class Actor
{
public:
	Actor(string filename, float x, float y, int width, int height, Game* game);
	~Actor();
	virtual void draw(float scrollX = 0, float scrollY = 0);
	bool isOverlap(Actor* actor);
	bool containsPoint(int pointX, int pointY); // contiene punto
	bool isInRender();
	void stopMovement();

	bool collisionUp;
	bool collisionDown;
	bool outRight;
	bool outLeft;

	SDL_Texture* texture;
	int x;
	int y;
	float vx;
	float vy;
	float possibleMovementX;
	float possibleMovementY;
	int width;
	int height;
	int fileWidth;
	int fileHeight;
	int movingTime = 0;
	bool moving = false;
	Game* game; // referencia al juego
};

