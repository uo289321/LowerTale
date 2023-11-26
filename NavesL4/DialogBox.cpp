#include "DialogBox.h"

DialogBox::DialogBox(string text, Game* game)
	: Actor("res/dialogbox.png", WIDTH / 2, HEIGHT - 50, 480, 100, game) {
	this->text = new AnimatedText(text, x, y, game);
	this->finished = false;
}

void DialogBox::update() {
	finished = this->text->update();
	

}

void DialogBox::draw(float scrollX, float scrollY) {
	Actor::draw();
	text->draw();
}

