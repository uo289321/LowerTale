#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/player.png", x, y, 32, 40, game) {

	orientation = game->orientationDown;
	state = game->stateMoving;
	
	aIdleRight = new Animation("res/player_moving_right.png", width, height,
		32, 40, 6, 1, true, game);
	aIdleLeft = new Animation("res/player_moving_left.png", width, height,
		32, 40, 6, 1, true, game);
	aIdleDown = new Animation("res/player_moving_down.png", width, height,
		32, 40, 6, 1, true, game);
	aIdleUp = new Animation("res/player_moving_up.png", width, height,
		32, 40, 6, 1, true, game);

	aMovingRight = new Animation("res/player_moving_right.png", width, height,
		128, 40, 6, 4, true, game);
	aMovingLeft = new Animation("res/player_moving_left.png", width, height,
		128, 40, 6, 4, true, game);
	aMovingUp = new Animation("res/player_moving_up.png", width, height,
		128, 40, 6, 4, true, game);
	aMovingDown = new Animation("res/player_moving_down.png", width, height,
		128, 40, 6, 4, true, game);

	animation = aIdleDown;

}

void Player::update() {

	if (throwTime > 0) {
		throwTime--;
	}

	bool endAnimation = animation->update();
	

	// Establecer orientación
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}
	if (vy > 0) {
		orientation = game->orientationDown;
	}
	if (vy < 0) {
		orientation = game->orientationUp;
	}


	// Selección de animación basada en estados
	
	if (state == game->stateMoving) {
		if (vx != 0 && vy == 0) {
			if (orientation == game->orientationRight) {
				animation = aMovingRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aMovingLeft;
			}
		}
		if (vx == 0 && vy == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeft;
			}
			if (orientation == game->orientationDown) {
				animation = aIdleDown;
			}
			if (orientation == game->orientationUp) {
				animation = aIdleUp;
			}
		}
		if (vy != 0 && vx == 0) {
			if (orientation == game->orientationUp) {
				animation = aMovingUp;
			}
			if (orientation == game->orientationDown) {
				animation = aMovingDown;
			}
		}
	}
}

void Player::heal(int healing) {
	this->health = this->health + healing > MAX_HEALTH ? MAX_HEALTH : this->health + healing;
}

bool Player::hurt(int dmg) {
	this->health -= dmg;
	return health <= 0;
}

void Player::pick(Item* item) {
	this->inventory.push_back(item);
}

bool Player::isInRange(Actor* actor) {
	if ((actor->containsPoint(x + TILE_WIDTH, y) && orientation == game->orientationRight)
		|| (actor->containsPoint(x - TILE_WIDTH, y) && orientation == game->orientationLeft)
		|| (actor->containsPoint(x, y + TILE_HEIGHT) && orientation == game->orientationDown)
		|| (actor->containsPoint(x, y - TILE_HEIGHT) && orientation == game-> orientationUp)) {
		return true;

	}
	else {
		return false;
	}
}

bool Player::isTouching(Actor* actor) {
	if ((actor->containsPoint(x + (TILE_WIDTH / 2.0 + 1), y) && orientation == game->orientationRight)
		|| (actor->containsPoint(x - (TILE_WIDTH / 2.0 + 1), y) && orientation == game->orientationLeft)
		|| (actor->containsPoint(x, y + (TILE_HEIGHT / 2.0 + 1)) && orientation == game->orientationDown)
		|| (actor->containsPoint(x, y - (TILE_HEIGHT / 2.0 + 1)) && orientation == game->orientationUp)) {
		return true;
	}
	else {
		return false;
	}
}

void Player::moveX(float axis) {
	if (vy == 0) {
		if (vx == 0) {
			if (axis == 1 && orientation != game->orientationRight) {
				orientation = game->orientationRight;
				movingCd = 20;

			}
			if (axis == -1 && orientation != game->orientationLeft && vx == 0) {
				orientation = game->orientationLeft;
				movingCd = 20;
			}
		}

		if (movingCd <= 0) {
			int tileCenterX = (x / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2;
			if (axis == 0) {
				if (abs(x - tileCenterX) == 0)	// sólo permitimos parar si se ha cruzado de casilla
					vx = axis * 4;
			}
			else
				vx = axis * 4;
		}

		movingCd--;
	}
	

}

void Player::moveY(float axis) {
	if (vx == 0) { 
		if (vy == 0) {
			if (axis == -1 && orientation != game->orientationUp) {
				orientation = game->orientationUp;
				movingCd = 20;
			}
			if (axis == 1 && orientation != game->orientationDown) {
				orientation = game->orientationDown;
				movingCd = 20;
			}
		}
		if (movingCd <= 0) {
			int tileCenterY = (y / TILE_HEIGHT) * TILE_HEIGHT + TILE_HEIGHT / 2;
			if (axis == 0) {
				if (abs(y - tileCenterY) == 0)	// sólo permitimos parar si se ha cruzado de casilla
					vy = axis * 4;
			}
			else
				vy = axis * 4;
		}
		movingCd--;
	}
	
}

void Player::draw(float scrollX, float scrollY) {

	animation->draw(x - scrollX, y - scrollY);

}

Plank* Player::throwPlank() {
	if (throwTime == 0) {
		throwTime = throwCadence;
		// Plank* plank = new Plank(x, y, game);
		if (orientation == game->orientationRight) {
			Plank* plank = new Plank(x + TILE_WIDTH, y, game, game->orientationRight);
			plank->vx = 4;
			plank->vy = 0;
		}
		else if (orientation == game->orientationLeft) {
			Plank* plank = new Plank(x - TILE_WIDTH, y, game, game->orientationLeft);
			plank->vx = -4; // Invertir
			plank->vy = 0;
		}
		else if (orientation == game->orientationDown) {
			Plank* plank = new Plank(x, y + TILE_HEIGHT, game, game->orientationDown);
			plank->vx = 0; 
			plank->vy = 4;
		}
		else if (orientation == game->orientationUp) {
			Plank* plank = new Plank(x, y - TILE_HEIGHT, game, game->orientationUp);
			plank->vx = 0;
			plank->vy = -4; // Invertir
		}
	}
	else {
		return NULL;
	}

}


