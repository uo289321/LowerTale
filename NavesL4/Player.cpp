#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/player.png", x, y, 22, 32, game) {

	orientation = game->orientationDown;
	state = game->stateMoving;

	
	aIdleRight = new Animation("res/player_moving_right.png", width, height,
		22, 32, 6, 1, true, game);
	aIdleLeft = new Animation("res/player_moving_left.png", width, height,
		22, 32, 6, 1, true, game);
	aIdleDown = new Animation("res/player_moving_down.png", width, height,
		22, 32, 6, 1, true, game);
	aIdleUp = new Animation("res/player_moving_up.png", width, height,
		22, 32, 6, 1, true, game);

	aMovingRight = new Animation("res/player_moving_right.png", width, height,
		66, 32, 6, 3, true, game);
	aMovingLeft = new Animation("res/player_moving_left.png", width, height,
		66, 32, 6, 3, true, game);
	aMovingUp = new Animation("res/player_moving_up.png", width, height,
		66, 32, 6, 3, true, game);
	aMovingDown = new Animation("res/player_moving_down.png", width, height,
		66, 32, 6, 3, true, game);
	

	animation = aMovingDown;

}

void Player::update() {
	timeTillNextXMove--;
	timeTillNextYMove--;

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
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aMovingRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aMovingLeft;
			}
		}
		if (vx == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeft;
			}
		}
		if (vy != 0) {
			if (orientation == game->orientationUp) {
				animation = aMovingUp;
			}
			if (orientation == game->orientationDown) {
				animation = aMovingDown;
			}
		}
		if (vy == 0) {
			if (orientation == game->orientationUp) {
				animation = aIdleUp;
			}
			if (orientation == game->orientationDown) {
				animation = aIdleDown;
			}
		}
	}
}

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveTileX(float axis) {
	if (timeTillNextXMove <= 0) {
		vx = axis * 32;
		timeTillNextXMove = 5;
	}
	else {
		vx = 0;
	}
	
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

void Player::moveTileY(float axis) {
	if (timeTillNextYMove <= 0) {
		vy = axis * 40;
		timeTillNextYMove = 5;
	}
	else {
		vy = 0;
	}
}

void Player::draw(float scrollX, float scrollY) {

	animation->draw(x - scrollX, y - scrollY);

}
