#pragma once
#include "Actor.h"
#include "AnimatedText.h"

class DialogBox : public Actor
{
public:
	DialogBox(string text);
	AnimatedText* text;
	bool update();
};

