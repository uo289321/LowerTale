#include "Space.h"

Space::Space(float gravity) {
	dynamicActors.clear();
	staticActors.clear();
	movableActors.clear();
}

void Space::update() {
	for (auto const& actor : dynamicActors) {

		// Aun no se han detectado choques
		actor->collisionUp = false;
		actor->collisionDown = false;
		actor->outLeft = true;
		actor->outRight = true;

		// MoverDerecha / izquierda
		updateMoveRight(actor);
		updateMoveLeft(actor);
		updateMoveTop(actor);
		updateMoveDown(actor);

	}

	for (auto const& actor : movableActors) {

		// Aun no se han detectado choques
		actor->collisionUp = false;
		actor->collisionDown = false;
		actor->outLeft = true;
		actor->outRight = true;

		// MoverDerecha / izquierda
		updateMoveRight(actor);
		updateMoveLeft(actor);
		updateMoveTop(actor);
		updateMoveDown(actor);

	}
}


void Space::updateMoveRight(Actor* dynamicAct) {
	if (dynamicAct->vx > 0) {
		int possibleMovement = dynamicAct->vx;
		dynamicAct->possibleMovementX = 4;
		// El mejor "idealmente" vx partimos de ese

		for (auto const& staticAct : staticActors) {
			int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
			int topDynamic = dynamicAct->y - dynamicAct->height / 2;
			int downDynamic = dynamicAct->y + dynamicAct->height / 2;

			int leftStatic = staticAct->x - staticAct->width / 2;
			int topStatic = staticAct->y - staticAct->height / 2;
			int downStatic = staticAct->y + staticAct->height / 2;

			// Alerta!, Elemento est�tico en la trayectoria.
			if ((rightDynamic + dynamicAct->vx) >= leftStatic
				&& rightDynamic <= leftStatic
				&& topStatic < downDynamic
				&& downStatic > topDynamic) {
				dynamicAct->stopMovement();
				// Comprobamos si la distancia al est�tico es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement >= leftStatic - rightDynamic) {
					// La distancia es MENOR que nuestro movimiento posible
					// Tenemos que actualizar el movimiento posible a uno menor
					possibleMovement = leftStatic - rightDynamic;
				}
			}
		}

		

		for (auto const& movableAct : movableActors) {
			if (movableAct != dynamicAct && movableAct -> possibleMovementX == 0) {
				int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
				int topDynamic = dynamicAct->y - dynamicAct->height / 2;
				int downDynamic = dynamicAct->y + dynamicAct->height / 2;

				int leftStatic = movableAct->x - movableAct->width / 2;
				int topStatic = movableAct->y - movableAct->height / 2;
				int downStatic = movableAct->y + movableAct->height / 2;

				// Alerta!, Elemento est�tico en la trayectoria.
				if ((rightDynamic + dynamicAct->vx) >= leftStatic
					&& rightDynamic <= leftStatic
					&& topStatic < downDynamic
					&& downStatic > topDynamic) {
					dynamicAct->stopMovement();
					// Comprobamos si la distancia al est�tico es menor
					// que nuestro movimientoPosible actual
					if (possibleMovement >= leftStatic - rightDynamic) {
						// La distancia es MENOR que nuestro movimiento posible
						// Tenemos que actualizar el movimiento posible a uno menor
						possibleMovement = leftStatic - rightDynamic;
					}
				}
			}
		}

		// Ya se han comprobado todos los est�ticos
		dynamicAct->x = dynamicAct->x + possibleMovement;
		dynamicAct->possibleMovementX = possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->vx = possibleMovement;
	}

}

void Space::updateMoveLeft(Actor* dynamicAct) {
	if (dynamicAct->vx < 0) {
		int possibleMovement = dynamicAct->vx;
		dynamicAct->possibleMovementX = possibleMovement;
		// El mejor "idealmente" vx partimos de ese

		for (auto const& staticAct : staticActors) {
			int leftDynamic = dynamicAct->x - dynamicAct->width / 2;
			int topDynamic = dynamicAct->y - dynamicAct->height / 2;
			int downDynamic = dynamicAct->y + dynamicAct->height / 2;

			int rightStatic = staticAct->x + staticAct->width / 2;
			int topStatic = staticAct->y - staticAct->height / 2;
			int downStatic = staticAct->y + staticAct->height / 2;

			// Alerta!, Elemento est�tico en la trayectoria.
			if ((leftDynamic + dynamicAct->vx) <= rightStatic
				&& leftDynamic >= rightStatic
				&& topStatic < downDynamic
				&& downStatic > topDynamic) {
				dynamicAct->stopMovement();
				// Comprobamos si la distancia al est�tico es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement <= rightStatic - leftDynamic) {
					// La distancia es MENOR que nuestro movimiento posible
					// Tenemos que actualizar el movimiento posible a uno menor
					possibleMovement = rightStatic - leftDynamic;
				}

			}

		}

		for (auto const& movableAct : movableActors) {
			if (movableAct != dynamicAct && movableAct->possibleMovementX == 0) {
				int leftDynamic = dynamicAct->x - dynamicAct->width / 2;
				int topDynamic = dynamicAct->y - dynamicAct->height / 2;
				int downDynamic = dynamicAct->y + dynamicAct->height / 2;

				int rightStatic = movableAct->x + movableAct->width / 2;
				int topStatic = movableAct->y - movableAct->height / 2;
				int downStatic = movableAct->y + movableAct->height / 2;

				// Alerta!, Elemento est�tico en la trayectoria.
				if ((leftDynamic + dynamicAct->vx) <= rightStatic
					&& leftDynamic >= rightStatic
					&& topStatic < downDynamic
					&& downStatic > topDynamic) {
					dynamicAct->stopMovement();
					// Comprobamos si la distancia al est�tico es menor
					// que nuestro movimientoPosible actual
					if (possibleMovement <= rightStatic - leftDynamic) {
						// La distancia es MENOR que nuestro movimiento posible
						// Tenemos que actualizar el movimiento posible a uno menor
						possibleMovement = rightStatic - leftDynamic;
					}

				}
			}
		}
		// Ya se han comprobado todos los est�ticos
		dynamicAct->x = dynamicAct->x + possibleMovement;
		dynamicAct->possibleMovementX = possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->vx = possibleMovement;
	}

}

void Space::updateMoveTop(Actor* dynamicAct) {
	if (dynamicAct->vy < 0) {
		int possibleMovement = dynamicAct->vy;
		dynamicAct->possibleMovementY = possibleMovement;
		// El mejor "idealmente" vy partimos de ese

		for (auto const& staticAct : staticActors) {
			int topDynamic = dynamicAct->y - dynamicAct->height / 2;
			int downDynamic = dynamicAct->y + dynamicAct->height / 2;
			int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
			int leftDynamic = dynamicAct->x - dynamicAct->width / 2;

			int topStatic = staticAct->y - staticAct->height / 2;
			int downStatic = staticAct->y + staticAct->height / 2;
			int rightStatic = staticAct->x + staticAct->width / 2;
			int leftStatic = staticAct->x - staticAct->width / 2;

			// Alerta!, Elemento est�tico en la trayectoria.
			if ((topDynamic + dynamicAct->vy) <= downStatic
				&& downDynamic > topStatic
				&& leftDynamic < rightStatic
				&& rightDynamic > leftStatic) {
				dynamicAct->stopMovement();
				// Comprobamos si la distancia al est�tico es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement <= downStatic - topDynamic) {
					// La distancia es MENOR que nuestro movimiento posible
					// Tenemos que actualizar el movimiento posible a uno menor
					possibleMovement = downStatic - topDynamic;
					dynamicAct->collisionUp = true;

					if (rightDynamic <= rightStatic) {
						dynamicAct->outRight = false;
					}
					if (leftDynamic >= leftStatic) {
						dynamicAct->outLeft = false;
					}
				}
			}
		}

		for (auto const& movableAct : movableActors) {
			if (movableAct != dynamicAct && movableAct->possibleMovementY == 0) {
				int topDynamic = dynamicAct->y - dynamicAct->height / 2;
				int downDynamic = dynamicAct->y + dynamicAct->height / 2;
				int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
				int leftDynamic = dynamicAct->x - dynamicAct->width / 2;

				int topStatic = movableAct->y - movableAct->height / 2;
				int downStatic = movableAct->y + movableAct->height / 2;
				int rightStatic = movableAct->x + movableAct->width / 2;
				int leftStatic = movableAct->x - movableAct->width / 2;

				// Alerta!, Elemento est�tico en la trayectoria.
				if ((topDynamic + dynamicAct->vy) <= downStatic
					&& downDynamic > topStatic
					&& leftDynamic < rightStatic
					&& rightDynamic > leftStatic) {
					dynamicAct->stopMovement();
					// Comprobamos si la distancia al est�tico es menor
					// que nuestro movimientoPosible actual
					if (possibleMovement <= downStatic - topDynamic) {
						// La distancia es MENOR que nuestro movimiento posible
						// Tenemos que actualizar el movimiento posible a uno menor
						possibleMovement = downStatic - topDynamic;
						dynamicAct->collisionUp = true;

						if (rightDynamic <= rightStatic) {
							dynamicAct->outRight = false;
						}
						if (leftDynamic >= leftStatic) {
							dynamicAct->outLeft = false;
						}
					}
				}
			}
		}

		// Ya se han comprobado todos los est�ticos
		dynamicAct->y = dynamicAct->y + possibleMovement;
		dynamicAct->possibleMovementY = possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->vy = possibleMovement;
	}


}

void Space::updateMoveDown(Actor* dynamicAct) {
	if (dynamicAct->vy > 0) {
		int possibleMovement = dynamicAct->vy;
		dynamicAct->possibleMovementY = possibleMovement;
		// El mejor "idealmente" vy partimos de ese

		for (auto const& staticAct : staticActors) {
			int topDynamic = dynamicAct->y - dynamicAct->height / 2;
			int downDynamic = dynamicAct->y + dynamicAct->height / 2;
			int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
			int leftDynamic = dynamicAct->x - dynamicAct->width / 2;

			int topStatic = staticAct->y - staticAct->height / 2;
			int downStatic = staticAct->y + staticAct->height / 2;
			int rightStatic = staticAct->x + staticAct->width / 2;
			int leftStatic = staticAct->x - staticAct->width / 2;

			// Alerta!, Elemento est�tico en la trayectoria.
			if ((downDynamic + dynamicAct->vy) >= topStatic
				&& topDynamic < downStatic
				&& leftDynamic < rightStatic
				&& rightDynamic > leftStatic) {
				dynamicAct->stopMovement();
				// Comprobamos si la distancia al est�tico es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement >= topStatic - downDynamic) {
					// La distancia es MENOR que nuestro movimiento posible
					// Tenemos que actualizar el movimiento posible a uno menor
					possibleMovement = topStatic - downDynamic;
					dynamicAct->collisionDown = true;

					if (rightDynamic <= rightStatic) {
						dynamicAct->outRight = false;
					}
					if (leftDynamic >= leftStatic) {
						dynamicAct->outLeft = false;
					}

				}
			}
		}

		for (auto const& movableAct : movableActors) {
			if (movableAct != dynamicAct && movableAct->possibleMovementY == 0) {
				int topDynamic = dynamicAct->y - dynamicAct->height / 2;
				int downDynamic = dynamicAct->y + dynamicAct->height / 2;
				int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
				int leftDynamic = dynamicAct->x - dynamicAct->width / 2;

				int topStatic = movableAct->y - movableAct->height / 2;
				int downStatic = movableAct->y + movableAct->height / 2;
				int rightStatic = movableAct->x + movableAct->width / 2;
				int leftStatic = movableAct->x - movableAct->width / 2;

				// Alerta!, Elemento est�tico en la trayectoria.
				if ((downDynamic + dynamicAct->vy) >= topStatic
					&& topDynamic < downStatic
					&& leftDynamic < rightStatic
					&& rightDynamic > leftStatic) {
					dynamicAct->stopMovement();
					// Comprobamos si la distancia al est�tico es menor
					// que nuestro movimientoPosible actual
					if (possibleMovement >= topStatic - downDynamic) {
						// La distancia es MENOR que nuestro movimiento posible
						// Tenemos que actualizar el movimiento posible a uno menor
						possibleMovement = topStatic - downDynamic;
						dynamicAct->collisionDown = true;

						if (rightDynamic <= rightStatic) {
							dynamicAct->outRight = false;
						}
						if (leftDynamic >= leftStatic) {
							dynamicAct->outLeft = false;
						}

					}
				}
			}
		}

		// Ya se han comprobado todos los est�ticos
		dynamicAct->y = dynamicAct->y + possibleMovement;
		dynamicAct->possibleMovementY = possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->vy = possibleMovement;
	}

}


void Space::addDynamicActor(Actor* actor) {
	dynamicActors.push_back(actor);
}

void Space::addStaticActor(Actor* actor) {
	staticActors.push_back(actor);
}

void Space::addMovableActor(Actor* actor) {
	movableActors.push_back(actor);
}

void Space::removeDynamicActor(Actor* actor) {
	dynamicActors.remove(actor);
}

void Space::removeStaticActor(Actor* actor) {
	staticActors.remove(actor);
}

void Space::removeMovableActor(Actor* actor) {
	movableActors.remove(actor);
}
