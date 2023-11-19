#include "DialogBox.h"

DialogBox::DialogBox(string text)
	: Actor("res/dialogbox.png", 0, HEIGHT - 100, 480, 100, game) {
	this->text = new AnimatedText(text, x, y, game);
}

bool DialogBox::update() {
	if (this->text->update()) {
		SDL_Delay(1000);
		return true;
	}
	return false;


}

