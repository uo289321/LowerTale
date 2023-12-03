#include "InventoryMenu.h"

InventoryMenu::InventoryMenu(Player* p, Game* game)
	: Actor("res/inventory.png", WIDTH * 0.85, HEIGHT * 0.5, INVENTORY_WIDTH, INVENTORY_HEIGHT, game)
{
	this->player = p;
	this->game = game;
	this->selected = -1;
	loadOptions();
}

void InventoryMenu::loadOptions() {
	list<Item*> pInv = player->inventory;
	float index = 0.1;
	for (Item* it : pInv) {
		Text* opt = new Text(it->name, this->x, HEIGHT * index, game);
		this->options.push_back(opt);
		index += 0.2;
	}

	if (options.size() > 0) {
		Text* firstOp = *(options.begin());
		firstOp->highlight();
		selected = 0;
	}
}

bool InventoryMenu::select() {
	if (player->inventory.size() == 0)
		return false;
	auto it = player->inventory.begin();
	std::advance(it, selected);
	Item* item = *it;
	player->heal(item->healing);
	player->inventory.remove(item);
	loadOptions();

	return true;
}

void InventoryMenu::moveDown()
{
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

void InventoryMenu::moveUp() {
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

void InventoryMenu::draw(float scrollX, float scrollY) {
	Actor::draw();

	for (Text* o : options) {
		o->draw();
	}
}
