#include "BattleMenu.h"

BattleMenu::BattleMenu(Enemy* enemy, BattleLayer* layer, Game* game)
{	
	Text* t = new Text("Atacar", WIDTH / 3, HEIGHT * 0.8, game);
	t->highlight();
	this->options.push_back(t);
	this->options.push_back(new Text("Usar objeto", WIDTH * 2 / 3, HEIGHT * 0.8, game));
	this->selected = 0;
	this->layer = layer;
	this->enemy = enemy;
	this->game = game;
	this->blockCd = BLOCK_CD;
	
	SDL_Delay(100); // para no seleccionar sin querer
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
	auto iter = options.begin();
	std::advance(iter, selected);
	Text* optionSelected = *iter;
	string content = optionSelected->content;
	if (content == "Atacar") {
		attack();
	}

	if (content == "Usar objeto") {
		layer->showInventory();
	}


}

void BattleMenu::attack() {
	hideOptions();
	// atacar
	// pasar a defensa
	layer->player->state = game->stateDefending;
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
	if (layer->player->state == game->stateBattle) {
		for (auto const& text : options) {
			text->draw();
		}
	}
}


void BattleMenu::blockDown() {
	if (blockCd <= 0) {

		blockCd = BLOCK_CD;
	}
}

void BattleMenu::blockUp() {
	if (blockCd <= 0) {

		blockCd = BLOCK_CD;
	}
}

void BattleMenu::blockRight() {
	if (blockCd <= 0) {

		blockCd = BLOCK_CD;
	}
}

void BattleMenu::blockLeft() {
	if (blockCd <= 0) {

		blockCd = BLOCK_CD;
	}
}
