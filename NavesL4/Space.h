#pragma once
#include "Actor.h"
#include <list>

class Space
{
public:
	Space(float gravity);
	void update();
	void updateMoveRight(Actor* dynamicAct);
	void updateMoveLeft(Actor* dynamicAct);
	void updateMoveTop(Actor* dynamicAct);
	void updateMoveDown(Actor* dynamicAct);
	void updateMoveRightMovable(Actor* movableAct);
	void updateMoveLeftMovable(Actor* movableAct);
	void updateMoveTopMovable(Actor* movableAct);
	void updateMoveDownMovable(Actor* movableAct);
	void addDynamicActor(Actor* actor);
	void addStaticActor(Actor* actor);
	void addMovableActor(Actor* actor);
	void removeDynamicActor(Actor* actor);
	void removeStaticActor(Actor* actor);
	void removeMovableActor(Actor* actor);
	float gravity;
	list<Actor*> dynamicActors;
	list<Actor*> staticActors;
	list<Actor*> movableActors;
};
