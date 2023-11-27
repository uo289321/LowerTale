#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Enemy.h"
class Enemy;
#include "Projectile.h"
#include "Text.h"
#include "Audio.h" 
#include "Tile.h"
#include "Space.h"
#include "CheckPoint.h"
#include "DialogBox.h"
#include "InventoryMenu.h"
#include "BattleMenu.h"
class BattleMenu;
#include "Item.h"
#include "Plank.h"
#include "Box.h"
#include <list>

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String

#define BUTTON_DELAY 10

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;

	void processControls() override;
	void processMovingState();

	void update() override;
	void draw() override;
	void loadMap(string level);
	void loadMapObject(char character, float x, float y);
	void keysToControls(SDL_Event event);
	void calculateScroll();
	void showDialog(string text);
	void showInventory();
	void switchToBattle(Enemy* enemy);
	void switchToBattle();
	
	Space* space;
	float scrollX;
	float scrollY;
	int mapWidth;
	int mapHeight;

	int lastState;


	Audio* audioBackground;
	Text* textPoints;
	int points;
	Player* player;
	Background* background;
	Background* backgroundMoving;
	Background* backgroundBattle;
	DialogBox* dialogBox;
	// BattleMenu* battleMenu;
	InventoryMenu* inventory;



	list<Tile*> tiles;
	list<Tile*> waters;
	list<Enemy*> enemies;
	list<CheckPoint*> checkPoints;
	list<Item*> items;
	list<Plank*> planks;

	list<Box*> boxes;

	bool controlInteract = false;
	int buttonDelay = BUTTON_DELAY;
	bool controlCancel = false;
	bool controlInventory = false;
	Enemy* controlBattle = NULL;
	int controlMoveY = 0;
	int controlMoveX = 0;
	bool controlThrow = false;

	int spawnX = -1;
	int spawnY = -1;


};

