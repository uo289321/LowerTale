#include "BattleMenu.h"

BattleMenu::BattleMenu()
	: Actor()
{	
	Text* t = new Text("Atacar", this->x + this->width / 3, this->y + this->height / 2, game);
	t->highlight();
	this->options.push_back(t);
	this->options.push_back(new Text("Usar objeto", this->x + this->width * 2 / 3, this->y + this->height / 2, game));	
	health = new Text("", WIDTH * 0.1 ,HEIGHT * 0.9, game);// ESCRIBIR VIDA DEL JUGADOR
}


void BattleMenu::selectNext() {
	if (selected < options.size() - 1)
		selected++;
}

void BattleMenu::selectPrevious() {
	if (selected > 0)
		selected--;
}

void BattleMenu::select() {
	


}

void BattleMenu::hideOptions() {
	for (auto const& text : options) {
		text->hide();
	}
}

void BattleMenu::showOptions() {
	for (auto const& text : options) {
		text->show();
	}
}

void BattleMenu::draw(float scrollX, float scrollY) {
	Actor::draw();
	for (auto const& text : options) {
		text->draw();
	}
	health->draw();
}


void BattleMenu::update(int health) {
	this->health->content = to_string(health) + " / 20";
}
