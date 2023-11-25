#pragma once
#include "Player.h"
#include <list>
#include "Text.h"

class InventoryMenu :
    public Actor
{
public:
    InventoryMenu(Player* player, Game* game);
    void select();
    void moveUp();
    void moveDown();
    void loadOptions();
    void draw(float scrollX = 0, float scrollY = 0) override;

    Player* player;
    Game* game;
    list<Text*> options;
    int selected;
};

