/*
 * PlayerController.cpp
 *
 *  Created on: 27 Nov 2014
 *      Author: webpigeon
 */

#include "PlayerController.h"

PlayerController::PlayerController() {
	// TODO Auto-generated constructor stub
	this->entity = NULL;
	this->firing = false;
	this->acceleration = DIR_NONE;
	this->turning = DIR_NONE;
}

void PlayerController::onBind(Entity* entity) {
	this->entity = entity;
}

void PlayerController::setAccelerating(int dir) {
	this->acceleration = dir;
}

void PlayerController::setTurning(int dir) {
	this->turning = dir;
}

void PlayerController::update(int delta){

	if (firing) {
	}

	if (acceleration != DIR_NONE) {
		b2Body* body = entity->getBody();
		b2Vec2 speed(0, acceleration * 150);
		b2Vec2 force = body->GetWorldVector(speed);
		body->ApplyForce(force, body->GetWorldCenter(), true);
	}

	if (turning != DIR_NONE) {
		b2Body* body = entity->getBody();
		float w = body->GetAngularVelocity();
		w += (turning * 0.5);

		if (w > 2) w = 2;
		if (w < -2) w = -2;

		body->SetAngularVelocity(w);
	}


}

PlayerController::~PlayerController() {
}

