#include "BattleMenu.h"

BattleMenu::BattleMenu(Game* game)
{	
	Text* t = new Text("Atacar", WIDTH / 3, HEIGHT * 0.8, game);
	t->highlight();
	this->options.push_back(t);
	this->options.push_back(new Text("Usar objeto", WIDTH * 2 / 3, HEIGHT * 0.8, game));	
	health = new Text("", WIDTH * 0.1 ,HEIGHT * 0.9, game);// ESCRIBIR VIDA DEL JUGADOR
}


void BattleMenu::selectNext() {
	if (selected < options.size() - 1) {
		selected++;
		auto iter = options.begin();
		std::advance(iter, selected - 1);
		Text* t = *iter;
		t->unhighlight();
		std::advance(iter, 1);
		t = *iter;
		t->highlight();
	}	
}

void BattleMenu::selectPrevious() {
	if (selected > 0) {
		selected--;
		auto iter = options.begin();
		std::advance(iter, selected);
		Text* t = *iter;
		t->highlight();
		std::advance(iter, 1);
		t = *iter;
		t->unhighlight();
	}
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

void BattleMenu::draw() {
	for (auto const& text : options) {
		text->draw();
	}
	health->draw();
}


void BattleMenu::update(int health) {

	this->health->content = to_string(health) + " / 20";
}
