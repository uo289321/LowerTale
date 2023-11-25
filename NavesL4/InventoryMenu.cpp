#include "InventoryMenu.h"

InventoryMenu::InventoryMenu(Player* p, Game* game)
	: Actor("res/inventory.png", WIDTH * 0.85, HEIGHT * 0.5, 120, 300, game)
{
	this->player = p;
	this->game = game;

	loadOptions();
}

void InventoryMenu::loadOptions() {
	list<Item*> pInv = player->inventory;
	float yBaseLine = this->y - this->height / 2;
	int index = 1.1;
	for (Item* it : pInv) {
		float y = this->y + index;
		Text* opt = new Text(it->name, this->x, yBaseLine * index, game);
		opt->y = opt->y + opt->height / 2;
		this->options.push_back(opt);
		index += 0.1;
	}
}

void InventoryMenu::select() {
	auto it = player->inventory.begin();
	
	player->heal(item->healing);
}

void InventoryMenu::moveDown()
{
	selected = selected - width < 0 ? selected : selected - width;
}

void InventoryMenu::moveUp() {
	selected = selected + width > this->options.size() ? selected : selected + width;
}

void InventoryMenu::draw(float scrollX, float scrollY) {
	Actor::draw();

	for (Text* o : options) {
		o->draw();
	}
}
