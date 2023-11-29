#include "DeadLayer.h"

DeadLayer::DeadLayer(Game* game)
	: Layer(game) {
	Text* t = new Text("Continuar", WIDTH * 0.33, HEIGHT * 0.8, game);
	t->highlight();
	options.push_back(t);
	options.push_back(new Text("Salir", WIDTH * 0.66, HEIGHT * 0.8, game));
	this->selected = 0;
	background = new Background("res/backgroundDead.png", WIDTH / 2, HEIGHT / 2, game);
}



void DeadLayer::processControls() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
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