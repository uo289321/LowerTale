#pragma once
#include "Layer.h"
#include "Background.h"
#include "BattleMenu.h"
class BattleMenu;
#include "Enemy.h"
#include "Player.h"
#include "InventoryMenu.h"
#include "Projectile.h"
#include <list>
#include "Shield.h"
#include "DialogBox.h"
#include "Audio.h"

#define BUTTON_DELAY 10
// #define DEFENSE_TIMER 600
#define DEFENSE_TIMER 30
#define PLAYERMODEL_WIDTH 24
#define PLAYERMODEL_HEIGHT 24

class BattleLayer : public Layer
{
public:
	BattleLayer(Enemy* enemy, Player* player, Game* game);
	void changeEnemy(Enemy* enemy);
	void init();
	void update() override;
	void draw() override;
	void processControls() override;
	void keysToControls(SDL_Event event);
	void attack();
	void showInventory();
	void switchToAttack();
	void switchToDefense();
	void finishCombat();
	void showDialog(string content);

	Audio* bgMusic;
	DialogBox* dialogBox;
	Actor* playerModel;
	InventoryMenu* inventory;
	BattleMenu* battleMenu;
	int buttonDelay = 0;
	Enemy* enemy;
	Player* player;
	Shield* shield;

	int defenseTimer = DEFENSE_TIMER;

	list<Projectile*> projectiles;

	Text* health;
	Text* enemyHealth;
	int controlMoveY = 0;
	int controlMoveX = 0;
	bool controlInteract;
	bool controlCancel;
	Background* background;

};

