#include "BattleLayer.h"

BattleLayer::BattleLayer(Enemy* enemy, Player* player, Game* game) 
	: Layer(game) {
	background = new Background("res/backgroundbattle.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	this->player = player;
	this->playerModel = new Actor("res/playerModel.png", WIDTH * 0.5, HEIGHT * 0.5, PLAYERMODEL_WIDTH, PLAYERMODEL_HEIGHT, game);
	this->enemy = enemy;
	this->shield = new Shield(game);
	gamePad = SDL_GameControllerOpen(0);
	init();
	health = new Text("vida del jugador", WIDTH * 0.15, HEIGHT * 0.92, game);
	enemyHealth = new Text(to_string(enemy->hp), WIDTH * 0.1, HEIGHT * 0.1, game);

}

void BattleLayer::processControls()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}

		// Cambio autom�tico de input
		// PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		// Procesar teclas
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		// Procesar Mando
		if (game->input == game->inputGamePad) {  // gamePAD
			gamePadToControls(event);
		}
	}

	if (player->state == game->stateBlocked && enemy->isDead())
		if (controlInteract || controlCancel) {
			finishCombat();
			controlInteract = false;
			controlCancel = false;
		}



	if (player->state == game->stateBattle) {
		if (controlMoveX > 0)
			battleMenu->selectNext();
		else if (controlMoveX < 0)
			battleMenu->selectPrevious();
		if (controlInteract) {
			battleMenu->select();
			controlInteract = false;
			if (enemy->isDead()) {
				this->enemyHealth->content = "HP: 0";
				showDialog("El enemigo ha sido derrotado.");
			}
			else {
				this->enemyHealth->content = "HP: " + to_string(enemy->hp);
			}
		}
	}

	if (player->state == game->stateDefending) {
		if (controlMoveX > 0) {
			shield->moveX(1);
		}
		else if (controlMoveX < 0) {
			shield->moveX(-1);
		}
		else if (controlMoveY > 0) {
			shield->moveY(1);
		}
		else if (controlMoveY < 0) {
			shield->moveY(-1);
		}

	}

	if (player->state == game->stateInventory) {
		if (controlMoveY > 0)
			inventory->moveDown();
		else if (controlMoveY < 0)
			inventory->moveUp();

		if (controlCancel) {
			inventory = NULL;
			player->state = game->stateBattle;
		}
		else if (controlInteract) {
			inventory->select();
			inventory = NULL;
			controlInteract = false;
			player->state = game->stateDefending;
		}
	}

	if (player->health <= 0) {
		game->activeLayer = game->deadLayer;
		game->deadLayer->init();
	}

	
}

void BattleLayer::showDialog(string content) {
	player->state = game->stateBlocked;
	dialogBox = new DialogBox(content, game);
}

void BattleLayer::finishCombat() {
	game->currentLevel++;
	game->gameLayer->init();
	game->activeLayer = game->gameLayer;
	
	player->state = game->stateMoving;
}

void BattleLayer::showInventory() {
	player->state = game->stateInventory;
	inventory = new InventoryMenu(player, game);
}

void BattleLayer::keysToControls(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_z: // interaccion
			if (buttonDelay <= 0) {
				controlInteract = true;
				buttonDelay = BUTTON_DELAY;
			}
			break;
		case SDLK_x:
			if (buttonDelay <= 0) {
				controlCancel = true;
				buttonDelay = BUTTON_DELAY;
			}
			break;
		}



	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_z:
			controlInteract = false;
			break;
		case SDLK_x:
			controlCancel = false;
			break;


		}
	}
}

void BattleLayer::gamePadToControls(SDL_Event event) {

	// Leer los botones
	bool buttonLeft = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	bool buttonRight = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	bool buttonUp = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_UP);
	bool buttonDown = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	bool buttonB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_B);
	// SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B
	// SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y
	cout << "botones:" << buttonA << "," << buttonB << endl;
	int stickX = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTX);
	cout << "stickX" << stickX << endl;

	// Retorna aproximadamente entre [-32800, 32800], el centro deber�a estar en 0
	// Si el mando tiene "holgura" el centro varia [-4000 , 4000]
	if (buttonRight) {
		controlMoveX = 1;
	}
	else if (buttonLeft) {
		controlMoveX = -1;
	}
	else {
		controlMoveX = 0;
	}

	if (buttonUp) {
		controlMoveY = -1;
	}
	else if (buttonDown) {
		controlMoveY = 1;
	}
	else {
		controlMoveY = 0;
	}

	if (buttonA) {
		if (buttonDelay <= 0) {
			controlInteract = true;
			buttonDelay = BUTTON_DELAY;
		}
	}
	else {
		controlInteract = false;
	}

	if (buttonB) {
		if (buttonDelay <= 0) {
			controlCancel = true;
			buttonDelay = BUTTON_DELAY;
		}
	}
	else {
		controlCancel = false;
	}
}

void BattleLayer::update() {

	bool dead = false;
	buttonDelay--;

	if (dialogBox != NULL)
		dialogBox->update();

	if(player->state == game->stateBattle || player->state == game->stateInventory)
		enemy->animation->update();


	if (player->state == game->stateDefending) {
		defenseTimer--;
		if (defenseTimer <= 0) {
			switchToAttack();
		}
		else {
			for (auto const& proj : projectiles)
				proj->update();

			Projectile* p = enemy->update();
			if (p != NULL) {
				projectiles.push_back(p);
			}


			list<Projectile*> deleteProjectiles;
			for (auto const& projectile : projectiles) {
				if (shield->isOverlap(projectile)) {
					blocked->play();
					bool pInList = std::find(deleteProjectiles.begin(),
						deleteProjectiles.end(),
						projectile) != deleteProjectiles.end();

					if (!pInList) {
						deleteProjectiles.push_back(projectile);
					}
				}
				else if (playerModel->isOverlap(projectile)) 
				{

					dead = player->hurt(enemy->damage);// restar vida al jugador

					bool pInList = std::find(deleteProjectiles.begin(),
						deleteProjectiles.end(),
						projectile) != deleteProjectiles.end();

					if (!pInList) {
						deleteProjectiles.push_back(projectile);
					}


				}

				
			}

			for (auto const& delProjectile : deleteProjectiles) {
				projectiles.remove(delProjectile);
				delete delProjectile;
			}
			deleteProjectiles.clear();

			
		}
		
		
	}

	if (dead) {
		health->content = "HP: 0 / 20";
		enemy->restore();
	}
	else {
		health->content = "HP: " + to_string(player->health) + " / 20";
	}
	
}

void BattleLayer::switchToDefense() {
	defenseTimer = DEFENSE_TIMER;
	player->state = game->stateDefending;
}

void BattleLayer::switchToAttack() {
	player->state = game->stateBattle;
	projectiles.clear();
}

void BattleLayer::attack() {
	int damageDone = rand()%(6 - 3 + 1) + 3;
	enemy->receiveDamage(damageDone);
	switchToDefense();
}

void BattleLayer::changeEnemy(Enemy* enemy) {
	this->enemy = enemy;
}

void BattleLayer::init()
{
	if (this->blocked != NULL) {
		blocked->~Audio();
	}
	this->battleMenu = new BattleMenu(this->enemy, this, game);
	this->blocked = new Audio("res/blocked.wav", false);
	this->bgMusic = new Audio("res/battleMusic.wav", true);
	bgMusic->play();
}

void BattleLayer::draw()
{
	background->draw(0,0);
	

	if (player->state == game->stateBattle || player->state == game->stateInventory) {
		enemy->drawAnim();
		
	}

	battleMenu->draw();
	health->draw();
	enemyHealth->draw();


	if (dialogBox != NULL)
		dialogBox->draw();

	if (inventory != NULL)
		inventory->draw();
	
	if (player->state == game->stateDefending) {
		playerModel->draw();
		for (auto const& proj : projectiles) {
			proj->draw();
		}
		shield->draw();
	}
	SDL_RenderPresent(game->renderer); // Renderiza
}
