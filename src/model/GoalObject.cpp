/*
 * GoalObject.cpp
 *
 *  Created on: 27 Nov 2014
 *      Author: webpigeon
 */

#include "GoalObject.h"
#include "Ship.h"

GoalObject::GoalObject(float32 x, float32 y, float32 size) : Entity(x, y, size) {
}

void GoalObject::init(Manager<Entity>* manager) {
	body = manager->buildBody(buildShipBodyDef(initPos.x, initPos.y));
	body->SetUserData(this);
	body->CreateFixture(buildShipFixtureDef());
}

void GoalObject::collidedWith(Entity* entity, Manager<Entity>* manager) {
	if (entity->getEntityType() == ENT_TYPE_BULLET) {
		manager->remove(this);
	}
}

int GoalObject::getEntityType() {
	return ENT_TYPE_GOAL;
}

GoalObject::~GoalObject() {
}

