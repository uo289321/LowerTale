#include "DeadLayer.h"

DeadLayer::DeadLayer(Game* game)
	: Layer(game) {
	background = new Background("res/backgroundDead.png", WIDTH / 2, HEIGHT / 2, game);
	gamePad = SDL_GameControllerOpen(0);
	
}

void DeadLayer::init() {

	options.clear();

	Text* t = new Text("Continuar", WIDTH * 0.33, HEIGHT * 0.8, game);
	t->highlight();
	options.push_back(t);
	options.push_back(new Text("Salir", WIDTH * 0.66, HEIGHT * 0.8, game));
	this->selected = 0;
	
	bgMusic = new Audio("res/dead.wav", true);
	bgMusic->play();
}



void DeadLayer::processControls() {
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

	if (controlMoveX > 0)
		selectNext();
	else if (controlMoveX < 0)
		selectPrevious();
	if (controlInteract) {
		select();
		controlInteract = false;
	}
}

void DeadLayer::keysToControls(SDL_Event event) {
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
		case SDLK_z: // interaccion
			controlInteract = true;
			break;


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
			case SDLK_z:
				controlInteract = false;
				break;
			}
		}
	}
}

void DeadLayer::gamePadToControls(SDL_Event event) {

	// Leer los botones
	bool buttonLeft = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	bool buttonRight = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	// SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B
	// SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y
	cout << "botones:" << buttonA << endl;
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

	if (buttonA) {
		controlInteract = true;
	}
	else {
		controlInteract = false;
	}
}


void DeadLayer::selectNext() {
	if (selected < options.size() - 1) {
		selected++;
		auto iter = options.begin();
		std::advance(iter, selected - 1);
		Text* t = *iter;
		t->unhighlight();
		std::advance(iter, 1);
		t = *iter;
		t->highlight();
	}
}

void DeadLayer::selectPrevious() {
	if (selected > 0) {
		selected--;
		auto iter = options.begin();
		std::advance(iter, selected);
		Text* t = *iter;
		t->highlight();
		std::advance(iter, 1);
		t = *iter;
		t->unhighlight();
	}
}

void DeadLayer::select() {
	auto iter = options.begin();
	std::advance(iter, selected);
	Text* optionSelected = *iter;
	string content = optionSelected->content;
	if (content == "Continuar") {
		GameLayer* gL = (GameLayer*) game->gameLayer;
		gL->init();
		game->activeLayer = game->gameLayer;
	}

	if (content == "Salir") {
		game->loopActive = false;
	}
}

void DeadLayer::update() {}

void DeadLayer::draw() {
	background->draw();
	for (auto const& text : options) {
		text->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}