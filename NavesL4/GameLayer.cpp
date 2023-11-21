#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {
	space = new Space(0);
	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	// audioBackground->play();

	player = new Player(50, 50, game);
	// background = new Background("res/background.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	backgroundMoving = new Background("res/background.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	backgroundBattle = new Background("res/backgroundbattle.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	background = backgroundMoving;

	enemies.clear(); // Vaciar por si reiniciamos el juego


	// loadMap("res/" + to_string(game->currentLevel) + ".txt");
	loadMap("res/test0.txt");
	switchToBattle();
}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 32; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 32 / 2 + j * 32; // x central
				float y = 40 + i * 40; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'E': {
		Enemy* enemy = new Enemy(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case '1': {
		player = new Player(x, y, game);
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		break;
	}
	case 'A': {
		CheckPoint* cp = new CheckPoint(x, y, game);
		cp->y = cp->y - cp->height / 2;
		checkPoints.push_back(cp);
		space->addDynamicActor(cp);
		break;
	}
	//case 'P': {
	//	Collectable* c = new Collectable(x, y, game);
	//	c->y = c->y - c->height / 2;
	//	collectables.push_back(c);
	//	space->addDynamicActor(c);
	//	break;
	//}
	//case 'Y': {
	//	Jumpboost* j = new Jumpboost(x, y, game);
	//	j->y = j->y - j->height / 2;
	//	jumpboosts.push_back(j);
	//	space->addDynamicActor(j);
	//	break;
	//}
	case 'B': {
		Tile* tile = new Tile("res/black.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '#': {
		Tile* tile = new Tile("res/pared.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	}
}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}
	// Eje X
	if (player->state == game->stateMoving) {
		if (controlMoveX > 0) {
			player->moveX(1);
		}
		else if (controlMoveX < 0) {
			player->moveX(-1);
		}
		else {
			player->moveX(0);
		}

		// Eje Y
		if (controlMoveY > 0) {
			player->moveY(1);
		}
		else if (controlMoveY < 0) {
			player->moveY(-1);
		}
		else {
			player->moveY(0);
		}
	}

	if (player->state == game->stateBattle) {
		if (controlMoveX > 0)
			battleMenu->selectNext();
		else if (controlMoveX < 0)
			battleMenu->selectPrevious();
	}

	if (player->state == game->stateBlocked) {
		if ((controlCancel || controlInteract) && dialogBox->finished) {
			dialogBox = NULL;
			player->state = game->stateMoving;
		}
	}

}

void GameLayer::update() {
	space->update();
	background->update();
	player->update();

	if (dialogBox != NULL)
		dialogBox->update();

	/*for (auto const& enemy : enemies) {
		enemy->update();
	}*/

	if (player->state == game->stateBattle)
		battleMenu->update(player->health);

	for (auto const& cp : checkPoints) {
		if (player->isInRange(cp) && controlInteract && player->state == game->stateMoving) {
			showDialog("Tus fuerzas se han renovado.");

			spawnY = player->y;
			spawnX = player->x;
		}
	}

	for (auto const& item : items) {
		if (player->isInRange(item) && controlInteract && player->state == game->stateMoving) {
			showDialog("¡Has encontrado el siguiente objeto: " + item->name);
		}
	}

	

	// Colisiones , Enemy - Projectile

	/*list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	for (auto const& projectile : projectiles) {
		if (projectile->isInRender() == false) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}*/



	/*for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				bool eInList = std::find(deleteEnemies.begin(),
					deleteEnemies.end(),
					enemy) != deleteEnemies.end();

				if (!eInList) {
					deleteEnemies.push_back(enemy);
				}

				points++;
				textPoints->content = to_string(points);


			}
		}
	}*/

	/*for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();*/


	cout << "update GameLayer" << endl;
}

void GameLayer::showDialog(string content) {
	player->state = game->stateBlocked;
	dialogBox = new DialogBox(content, game);
}

void GameLayer::draw() {
	calculateScroll();

	background->draw(scrollX, scrollY);
	if (player->state == game->stateBattle) {
		battleMenu->draw();
	}
	else {
		for (auto const& tile : tiles) {
			tile->draw(scrollX, scrollY);
		}
		player->draw(scrollX, scrollY);
		for (auto const& enemy : enemies) {
			enemy->draw(scrollX, scrollY);
		}
		for (auto const& cp : checkPoints) {
			cp->draw(scrollX, scrollY);
		}

		if (dialogBox != NULL)
			dialogBox->draw(scrollX, scrollY);
	}
	/*for (auto const& projectile : projectiles) {
		projectile->draw();
	}*/
	
	
	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::switchToBattle() {

	player->state = game->stateBattle;
	battleMenu = new BattleMenu(game);
	background = backgroundBattle;
}
// Si el jugador está en movimiento no permitimos acciones
void GameLayer::keysToControls(SDL_Event event) {
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
			controlInteract = true;
			break;
		case SDLK_x:
			controlCancel = true;
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
			}

		}

}

void GameLayer::calculateScroll() {
	// limite izquierda
	if (player->x > WIDTH * 0.3) {
		if (player->x - scrollX < WIDTH * 0.3) {
			scrollX = player->x - WIDTH * 0.3;
		}
	}

	// limite derecha
	if (player->x < mapWidth - WIDTH * 0.3) {
		if (player->x - scrollX > WIDTH * 0.7) {
			scrollX = player->x - WIDTH * 0.7;
		}
	}


	if (player->y - scrollY > HEIGHT * 0.7) {
		scrollY = player->y - HEIGHT * 0.7;
	}

	if (player->y - scrollY < HEIGHT * 0.3) {
		scrollY = player->y - HEIGHT * 0.3;
	}

}

