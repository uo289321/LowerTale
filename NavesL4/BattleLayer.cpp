#include "BattleLayer.h"

BattleLayer::BattleLayer(Enemy* enemy, Player* player, Game* game) 
	: Layer(game) {
	background = new Background("res/backgroundbattle.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	this->player = player;
	this->playerModel = new Actor("res/icono_puntos.png", WIDTH * 0.5, HEIGHT * 0.5, PLAYERMODEL_WIDTH, PLAYERMODEL_HEIGHT, game);
	this->enemy = enemy;
	this->shield = new Shield(game);
	init();
	health = new Text("vida del jugador", WIDTH * 0.15, HEIGHT * 0.92, game);// ESCRIBIR VIDA DEL JUGADOR
}

void BattleLayer::processControls()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
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
				game->activeLayer = game->gameLayer;
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
			player->state = game->stateDefending;
		}
	}

	
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

void BattleLayer::update() {

	bool dead = false;
	buttonDelay--;

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
		health->content = "0 / 20";
		enemy->restore();
	}
	else {
		health->content = to_string(player->health) + " / 20";
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
	int damageDone = 10;
	enemy->receiveDamage(damageDone);
	switchToDefense();
}

void BattleLayer::changeEnemy(Enemy* enemy) {
	this->enemy = enemy;
}

void BattleLayer::init()
{
	this->battleMenu = new BattleMenu(this->enemy, this, game);
}

void BattleLayer::draw()
{
	background->draw(0,0);
	health->draw();
	battleMenu->draw();

	if (inventory != NULL)
		inventory->draw();

	if (player->state == game->stateBattle || player->state == game->stateInventory) {
		enemy->drawAnim();
		
	}
	
	if (player->state == game->stateDefending) {
		playerModel->draw();
		for (auto const& proj : projectiles) {
			proj->draw();
		}
		shield->draw();
	}


	


	SDL_RenderPresent(game->renderer); // Renderiza
}
