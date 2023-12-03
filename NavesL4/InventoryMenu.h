#pragma once
#include "Player.h"
#include <list>
#include "Text.h"
#include "Item.h"

#define INVENTORY_WIDTH 120
#define INVENTORY_HEIGHT 240

class InventoryMenu :
    public Actor
{
public:
    InventoryMenu(Player* player, Game* game);
    bool select();
    void moveUp();
    void moveDown();
    void loadOptions();
    void draw(float scrollX = 0, float scrollY = 0) override;

    Player* player;
    Game* game;
    list<Text*> options;
    list<Item*> items;
    int selected;
};

