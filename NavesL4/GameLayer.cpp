#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	pause = true;
	message = new Actor("res/como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);
	gamePad = SDL_GameControllerOpen(0);
	init();
}
	

void GameLayer::init() {
	space = new Space(0);
	audioBackground = new Audio("res/game.wav", true);
	audioBackground->play();

	player = new Player(50, 50, game);
	background = new Background("res/background0.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	audioOpenDoor = new Audio("res/open_door_aud.wav", false);

	enemies.clear(); // Vaciar por si reiniciamos el juego
	checkPoints.clear();
	planks.clear();
	boxes.clear();
	pressurePlates.clear();
	switches.clear();
	xos.clear();
	tiles.clear();
	waters.clear();
	items.clear();
	floorPlanks.clear();
	door = NULL;

	if (game->currentLevel >= game->nLevels) {
		game->currentLevel = 0;
	}


	
	// loadMap("res/test0.txt");
	loadMap("res/" + to_string(game->currentLevel) + ".txt");
}

void GameLayer::respawn() {
	game->currentLevel = game->savedLevel;
	init();
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
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'E': {
		Enemy* enemy = new Enemy("enemyE", 20, 5, 15, x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addStaticActor(enemy);
		break;
	}
	case 'G': {
		Enemy* enemy = new Enemy("enemyG", 20, 6, 13, x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addStaticActor(enemy);
		break;
	}
	case 'H': {
		Enemy* enemy = new Enemy("enemyH", 20, 8, 11, x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addStaticActor(enemy);
		break;
	}
	case '1': {
		if (spawnX != -1 && game->savedLevel == game->currentLevel)	// si hay un guardado en este nivel
			player = new Player(spawnX, spawnY, game);
		else
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
		space->addStaticActor(cp);
		break;
	}
	case 'F': {
		Item* item = new Item("Filete", x, y, 5, game);
		item->y = item->y - item->height / 2;
		items.push_back(item);
		space->addStaticActor(item);
		break;
	}
	case 'Q': {
		Box* box = new Box(x, y, game);
		box->y = box->y - box->height / 2;
		boxes.push_back(box);
		space->addDynamicActor(box);
		break;
	}
	case 'P': {
		PressurePlate* p = new PressurePlate(x, y, game);
		p->y = p->y - p->height / 2;
		pressurePlates.push_back(p);
		space->addDynamicActor(p);
		break;
	}
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
	case 'R': {
		Tile* tile = new Tile("res/paredDerecha.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'L': {
		Tile* tile = new Tile("res/paredIzquierda.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'W': {
		Tile* water = new Tile("res/water.png", x, y, game);
		// Tile* water = new Tile("res/water.png", x, y, game);
		water->y = water->y - water->height / 2;
		waters.push_back(water);
		space->addStaticActor(water);
		break;
	}
	case 'D': {
		door = new Door("res/closed_door.png", x, y, game);
		door->y = door->y - door->height / 2;
		space->addStaticActor(door);
		break;
	}
	case 'S': {
		Switch* sw = new Switch(nOfSwitch, x, y, game);
		sw->y = sw->y - sw->height / 2;
		switches.push_back(sw);
		space->addStaticActor(sw);
		nOfSwitch++;
		break;
	}
	case 'T': {
		Plank* pl = new Plank("res/plank.png", x, y, game, game->orientationRight);
		pl->y = pl->y - pl->height / 2;
		floorPlanks.push_back(pl);
		space->addStaticActor(pl);
		break;
	}
	case 'U': {
		Tile* tile = new Tile("res/paredArriba.png", x, y, game);
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
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}

		// Cambio automático de input
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

	if (controlThrow && player->hasPlank) {
		Plank* newPlank = player->throwPlank();
		bool generated = false;
		for (Tile* water : waters) {
			if (newPlank != NULL && player->isTouching(water) && !generated) {
				planks.push_back(newPlank);
				generated = true;
				player->hasPlank = false;
			}
		}
	}

	// Eje X
	if (player->state == game->stateMoving) {
		processMovingState();
	}

	if (player->state == game->stateBlocked) {
		if ((controlInteract || controlCancel) && dialogBox->finished) {
			dialogBox = NULL;
			controlInteract = false;
			controlCancel = false;
			player->state = game->stateMoving;
		}
	}

	if (player->state == game->stateInventory) {
		if (controlMoveY < 0)
			inventory->moveDown();
		else if (controlMoveY > 0)
			inventory->moveUp();
		if (controlInteract) {
			int beforeHP = player->health;
			if (inventory->select()) {
				showDialog("Has recuperado " + to_string(player->health - beforeHP) + "HP!");
			}
			inventory = NULL;
		}
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

	if (controlContinue) {
		pause = false;
		controlContinue = false;
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

	
}

void GameLayer::update() {
	if (pause) {
		return;
	}

	buttonDelay--;

	space->update();
	background->update();
	player->update();

	if (dialogBox != NULL)
		dialogBox->update();

	for (auto const& box : boxes) {
		if (player->canMoveActor(box)) {
			box->vx = player->vx;
			box->vy = player->vy;
		}
		else {
			box->vx = 0;
			box->vy = 0;
		}
	}

	for (auto const& cp : checkPoints) {
		if (player->isInRange(cp) && controlInteract && player->state == game->stateMoving) {
			showDialog("Tus fuerzas se han renovado.");
			player->heal(MAX_HEALTH);
			spawnY = player->y + player->height / 2;
			spawnX = player->x;
			game->savedLevel = game->currentLevel;
			controlInteract = false;
		}
	}

	for (Plank* plank : planks) {
		if (plank->canMove(waters, planks)) {
			plank->update();
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

	for (PressurePlate* pp : pressurePlates) {
		if (pp->isPressed(boxes)) {
			pp->is_pressed = true;
			cout << "Presionada" << endl;
		}
		else {
			pp->is_pressed = false;
		}
	}

	int i = 0;
	for (PressurePlate* pp : pressurePlates) {
		if (pp->is_pressed) {
			i++;
		}
	}

	int j = 0;
	for (Switch* sw : switches) {
		if (sw->active) {
			j++;
		}
	}

	if (i == pressurePlates.size() && j == switches.size()) {
		if (door != NULL && !door->is_open) {
			space->removeStaticActor(door);
			audioOpenDoor->play();
			door = new Door("res/open_door.png", door->x, door->y, game);
			door->is_open = true;
			space->addDynamicActor(door);
		}
	}

	if (i < pressurePlates.size() || j < switches.size()) {
		if (door != NULL && door->is_open) {
			space->removeDynamicActor(door);
			audioOpenDoor->play();
			door = new Door("res/closed_door.png", door->x, door->y, game);
			door->is_open = false;
			space->addStaticActor(door);
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

	Plank* removePlank = NULL;
	for (auto const& plank : floorPlanks) {
		if (player->isInRange(plank) && controlInteract && player->state == game->stateMoving && !player->hasPlank) {
			showDialog("Has recogido una tabla");
			removePlank = plank;
			player->hasPlank = true;
			controlInteract = false;

		}
	}
	if (removePlank != NULL) {
		floorPlanks.remove(removePlank);
		space->removeStaticActor(removePlank);

	}
	

	for (auto const& sw : switches) {
		if (player->isInRange(sw) && controlInteract && player->state == game->stateMoving) {
			if (sw->active) {
				showDialog("Boton desactivado");
			}
			else {
				showDialog("Boton activado");
			}
			sw->flick();
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

	for (Plank* plank : planks) {
		for (Tile* water : waters) {
			if (plank->isOnTopOf(water) && plank->vx == 0 && plank->vy == 0) {
				space->addDynamicActor(water);
				space->removeStaticActor(water);
			}
		}
	}
	list<Enemy*> delEnemies;
	for (auto const& en : enemies) {
		if (en->isDead())
			delEnemies.push_back(en);
	}

	for (Enemy* en : delEnemies) {
		enemies.remove(en);
		space->removeStaticActor(en);
	}
	delEnemies.clear();	

	for (auto const& enemy : enemies) {
		if (player->isInRange(enemy) && controlInteract && player->state == game->stateMoving) {
			switchToBattle(enemy);
		}
	}

	for (auto const& xo : xos)
	{
		if (player->isOverlap(xo) && !xo->playerStanding) {	// pisa el tile por primera vez
			xo->change();
			xo->playerStanding = true;
		}
		else if(!player->isOverlap(xo)) {
			xo->playerStanding = false;
		}
	}

	// cout << "update GameLayer" << endl;
}

void GameLayer::showDialog(string content) {
	// this->lastState = player->state;
	switchToBlock();
	dialogBox = new DialogBox(content, game);
}

void GameLayer::switchToBlock() {
	player->state = game->stateBlocked;
	player->vx = 0;
	player->vy = 0;
	
	player->moveX(0);
	player->moveY(0);
}

void GameLayer::showInventory() {
	// this->lastState = player->state;
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
	for (auto const& pp : pressurePlates) {
		pp->draw(scrollX, scrollY);
	}
	for (auto const& xo : xos) {
		xo->draw(scrollX, scrollY);
	}
	for (auto const& sw : switches) {
		sw->draw(scrollX, scrollY);
	}
	for (auto const& cp : checkPoints) {
		cp->draw(scrollX, scrollY);
	}

	player->draw(scrollX, scrollY);

	if (door != NULL) {
		door->draw(scrollX, scrollY);
	}
	for (auto const& item : items) {
		item->draw(scrollX, scrollY);
	}

	for (auto const& plank : floorPlanks) {
		plank->draw(scrollX, scrollY);
	}

	for (auto const& enemy : enemies) {
		enemy->draw(scrollX, scrollY);
	}

	for (auto const& box : boxes) {
		box->draw(scrollX, scrollY);
	}

	if (dialogBox != NULL)
		dialogBox->draw(scrollX, scrollY);



	if (inventory != NULL)
		inventory->draw(scrollX, scrollY);

	if (pause) {
		message->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::switchToBattle(Enemy* enemy) {
	controlBattle = enemy;
	controlInteract = false;

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
			if (buttonDelay <= 0 && controlMoveX == 0 && controlMoveY == 0) {
				controlInteract = true;
				buttonDelay = BUTTON_DELAY;
			}
			break;
		case SDLK_x:
			if (buttonDelay <= 0 && controlMoveX == 0 && controlMoveY == 0) {
				controlCancel = true;
				buttonDelay = BUTTON_DELAY;
			}
			break;
		case SDLK_c:
			if (buttonDelay <= 0 && controlMoveX == 0 && controlMoveY == 0) {
				controlInventory = true;
				buttonDelay = BUTTON_DELAY;
			}
			break;
		case SDLK_q:
			controlThrow = true;
		}

		if (code != SDLK_1) {
			controlContinue = true;
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
		case SDLK_q:
			controlThrow = false;
			break;
		}
	}
}

void GameLayer::gamePadToControls(SDL_Event event) {

	// Leer los botones
	bool buttonLeft = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	bool buttonRight = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	bool buttonUp = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_UP);
	bool buttonDown = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	bool buttonB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_B);
	bool buttonX = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_X);
	bool buttonY = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_Y);
	// SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B
	// SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y
	cout << "botones:" << buttonA << "," << buttonB << endl;
	int stickX = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTX);
	cout << "stickX" << stickX << endl;

	// Retorna aproximadamente entre [-32800, 32800], el centro debería estar en 0
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
		controlInteract = true;
	}
	else {
		controlInteract = false;
	}

	if (buttonB) {
		controlCancel = true;
	}
	else {
		controlCancel = false;
	}

	if (buttonX) {
		controlInventory = true;
	}
	else {
		controlInventory = false;
	}

	if (buttonY) {
		controlThrow = true;
	}
	else {
		controlThrow = false;
	}
	controlContinue = true;
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

