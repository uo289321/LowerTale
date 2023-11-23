#include "NavegationMenu.h"

NavegationMenu::NavegationMenu(float x, float y, int width, int height, list<Text*> options, Game* game)
	: Actor("black.png", x, y, width, height, game)
{
	this->options = options;
	selected = 0;
}

void NavegationMenu::moveLeft()
{
	selected = selected - 1 < 0 ? selected : selected - 1;
}

void NavegationMenu::moveRight() {
	selected = selected + 1 >= this->options.size() ? selected : selected + 1;
}

void NavegationMenu::moveDown() 
{
	selected = selected - width < 0 ? selected : selected - width;
}

void NavegationMenu::moveUp() {
	selected = selected + width > this->options.size() ? selected : selected + width;
}

void NavegationMenu::draw(float scrollX, float scrollY) {
	for (Text* t : options)
		t->draw();
}