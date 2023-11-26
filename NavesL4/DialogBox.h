#pragma once
#include "Actor.h"
#include "AnimatedText.h"

class DialogBox : public Actor
{
public:
	DialogBox(string text, Game* game);
	AnimatedText* text;
	void update();
	void draw(float scrollX = 0, float scrollY = 0) override;

	bool finished;
};

