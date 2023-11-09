#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/player.png", x, y, 22, 32, game) {

	orientation = game->orientationDown;
	state = game->stateMoving;



	
	aIdleRight = new Animation("res/player_idle_right.png", width, height,
		66, 40, 6, 3, true, game);
	aIdleLeft = new Animation("res/player_idle_left.png", width, height,
		66, 40, 6, 3, true, game);
	aIdleDown = new Animation("res/player_idle_down.png", width, height,
		66, 40, 6, 3, true, game);
	aIdleUp = new Animation("res/player_idle_up.png", width, height,
		66, 32, 6, 3, true, game);

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

	bool endAnimation = animation->update();


	// Establecer orientación
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
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
	}
}

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

void Player::draw(float scrollX, float scrollY) {


	animation->draw(x - scrollX, y - scrollY);

}
