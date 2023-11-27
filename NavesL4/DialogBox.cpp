#include "DialogBox.h"

DialogBox::DialogBox(string text, Game* game)
	: Actor("res/dialogBox.png", WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT, game) {
	this->text = new AnimatedText(text, WIDTH / 2, HEIGHT * 0.8, game);
	this->finished = false;
}

void DialogBox::update() {
	finished = this->text->update();
	

}

void DialogBox::draw(float scrollX, float scrollY) {
	Actor::draw();
	text->draw();
}

