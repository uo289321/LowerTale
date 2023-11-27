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
	backgroundMoving = new Background("res/background.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	// backgroundBattle = new Background("res/backgroundbattle.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	background = backgroundMoving;

	enemies.clear(); // Vaciar por si reiniciamos el juego
	checkPoints.clear();
	planks.clear();

	// loadMap("res/" + to_string(game->currentLevel) + ".txt");
	loadMap("res/test0.txt");
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
				float x = TILE_WIDTH / 2 + j * TILE_WIDTH; // x central
				float y = TILE_HEIGHT + i * TILE_HEIGHT; // y suelo
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
		Enemy* enemy = new Enemy("enemy1", 15, x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addStaticActor(enemy);
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
	case 'S': {
		Item* item = new Item("Filete", x, y, 5, game);
		item->y = item->y - item->height / 2;
		items.push_back(item);
		space->addStaticActor(item);
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
	case 'W':
		Tile * water = new Tile("res/water.png", x, y, game);
		// Tile* water = new Tile("res/water.png", x, y, game);
		water->y = water->y - water->height / 2;
		waters.push_back(water);
		space->addStaticActor(water);
		break;
	}
}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}



	if (controlThrow) {
		Plank* newPlank = player->throwPlank();
		bool generated = false;
		for (Tile* water : waters) {
			if (newPlank != NULL && player->isTouching(water) && !generated) {
				planks.push_back(newPlank);
				generated = true;
			}
		}
	}

	// Eje X
	if (player->state == game->stateMoving) {
		processMovingState();
	}

	/*if (player->state == game->stateBattle) {
		if (controlMoveX > 0)
			battleMenu->selectNext();
		else if (controlMoveX < 0)
			battleMenu->selectPrevious();
		if (controlInteract)
			battleMenu->select();
	}*/

	/*if (player->state == game->stateDefending) {
		if (controlMoveX > 0) {
			battleMenu->blockRight();
		}
		else if (controlMoveX < 0) {
			battleMenu->blockLeft();
		}
		else if (controlMoveY > 0) {
			battleMenu->blockDown();
		}
		else if (controlMoveY < 0) {
			battleMenu->blockUp();
		}

	}*/

	if (player->state == game->stateBlocked) {
		if ((controlInteract || controlCancel) && dialogBox->finished) {
			dialogBox = NULL;
			controlInteract = false;
			controlCancel = false;
		}
	}

	if (player->state == game->stateInventory) {
		if (controlCancel) {
			inventory = NULL;
			player->state = game->stateMoving;
		}
	}

	if (controlBattle != NULL) {
		player->state = game->stateBattle;
		game->activeLayer = new BattleLayer(controlBattle, player, game);
		controlBattle = NULL;
	}


}

void GameLayer::processMovingState() {
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

	if (controlInventory)
		showInventory();

	if (player->state == game->stateBlocked) {
		if ((controlInteract || controlCancel) && dialogBox->finished) {
			dialogBox = NULL;
		}
	}

	if (player->state == game->stateInventory) {
		if (controlCancel) {
			inventory = NULL;
			player->state = game->stateMoving;
		}
	}
}

void GameLayer::update() {
	buttonDelay--;
	space->update();
	background->update();
	player->update();

	if (dialogBox != NULL)
		dialogBox->update();

	for (auto const& cp : checkPoints) {
		if (player->isInRange(cp) && controlInteract && player->state == game->stateMoving) {
			showDialog("Tus fuerzas se han renovado.");

			spawnY = player->y;
			spawnX = player->x;
			controlInteract = false;
		}
	}

	for (Plank* plank : planks) {
		if (plank->canMove(waters, planks)) {
			plank->update();
			cout << "plankSpeed" << plank->vy << endl;
		}
		else {
			plank->vx = 0;
			plank->vy = 0;
		}
	}
	for (Plank* plank : planks) {
		for (Tile* water : waters) {
			if (plank->isOnTopOf(water) && plank->vx == 0 && plank->vy == 0) {
				space->removeStaticActor(water);
				space->addDynamicActor(water);
			}
		}
	}

	Item* removeItem = NULL;
	for (auto const& item : items) {
		if (player->isInRange(item) && controlInteract && player->state == game->stateMoving) {
			showDialog("Has recogido el siguiente objeto: " + item->name);
			removeItem = item;
			player->pick(item);
			controlInteract = false;
			
		}
	}
	if (removeItem != NULL) {
		items.remove(removeItem);
		space->removeStaticActor(removeItem);

	}

	if (player->state == game->stateBlocked && dialogBox == NULL) {
		player->state = game->stateMoving;
		SDL_Delay(100);

		for (Plank* plank : planks) {
			for (Tile* water : waters) {
				if (plank->isOnTopOf(water) && plank->vx == 0 && plank->vy == 0) {
					space->addDynamicActor(water);
					space->removeStaticActor(water);
				}
			}
		}

		Item* removeItem = NULL;
		for (auto const& item : items) {
			if (player->isInRange(item) && controlInteract && player->state == game->stateMoving) {
				showDialog("Has recogido el siguiente objeto: " + item->name);
				removeItem = item;
				player->pick(item);

			}
		}

		if (removeItem != NULL) {
			items.remove(removeItem);
			space->removeStaticActor(removeItem);
		}
	}

	for (auto const& enemy : enemies) {
		if (player->isInRange(enemy) && controlInteract && player->state == game->stateMoving) {
			switchToBattle(enemy);
		}
	}

	// cout << "update GameLayer" << endl;
}

void GameLayer::showDialog(string content) {
	this->lastState = player->state;
	player->state = game->stateBlocked;
	dialogBox = new DialogBox(content, game);
}

void GameLayer::showInventory() {
	this->lastState = player->state;
	player->state = game->stateInventory;
	inventory = new InventoryMenu(player, game);
	controlInventory = false;
}

void GameLayer::draw() {
	calculateScroll();

	background->draw(scrollX, scrollY);


		for (auto const& tile : tiles) {
			tile->draw(scrollX, scrollY);
		}
		for (auto const& water : waters) {
			water->draw(scrollX, scrollY);
		}
		for (auto const& plank : planks) {
			plank->draw(scrollX, scrollY);
		}
		player->draw(scrollX, scrollY);
		
		for (auto const& cp : checkPoints) {
			cp->draw(scrollX, scrollY);
		}

		for (auto const& item : items) {
			item->draw(scrollX, scrollY);
		}

	for (auto const& enemy : enemies) {
		enemy->draw(scrollX, scrollY);
	}
	

	if (dialogBox != NULL)
		dialogBox->draw(scrollX, scrollY);

	if (inventory != NULL)
		inventory->draw(scrollX, scrollY);

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::switchToBattle(Enemy* enemy) {
	controlBattle = enemy;
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
		case SDLK_c:
			if (buttonDelay <= 0) {
				controlInventory = true;
				buttonDelay = BUTTON_DELAY;
			}
			break;
		case SDLK_p:
			controlThrow = true;
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
		case SDLK_c:
			controlInventory = false;
			break;
		case SDLK_p:
			controlThrow = false;
			break;
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

