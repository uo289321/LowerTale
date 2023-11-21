#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Audio.h" 
#include "Tile.h"
#include "Space.h"
#include "CheckPoint.h"
#include "Item.h"
#include <list>
#include "DialogBox.h"
#include "BattleMenu.h"
class BattleMenu;

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void loadMap(string level);
	void loadMapObject(char character, float x, float y);
	void keysToControls(SDL_Event event);
	void calculateScroll();
	void showDialog(string text);
	void switchToBattle(Enemy* enemy);
	
	Space* space;
	float scrollX;
	float scrollY;
	int mapWidth;
	int mapHeight;


	Audio* audioBackground;
	Text* textPoints;
	int points;
	Player* player;
	Background* background;
	Background* backgroundMoving;
	Background* backgroundBattle;
	DialogBox* dialogBox;
	BattleMenu* battleMenu;

	list<Tile*> tiles;
	list<Enemy*> enemies;
	list<CheckPoint*> checkPoints;
	list<Item*> items;


	bool controlInteract = false;
	bool controlCancel = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	int spawnX = -1;
	int spawnY = -1;


};

