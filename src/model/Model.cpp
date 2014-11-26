/*
 * Model.cpp
 *
 *  Created on: 23 Nov 2014
 *      Author: webpigeon
 */

#include "Model.h"
#include "Entity.h"
#include <iostream>

#define WEAPON_COOLDOWN 500

using namespace std;

Model::Model(World* world, Entity* player) {
	this->world = world;
	this->score = 0;
	this->player = player;
	this->weaponLastFired = 0;
}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

Entity* Model::getPlayer(){
	return this->player;
}

void Model::BeginContact(b2Contact* contact){
	b2Body* b1 = contact->GetFixtureA()->GetBody();
	b2Body* b2 = contact->GetFixtureB()->GetBody();

	Entity* entity1 = NULL;
	Entity* entity2 = NULL;

	void* userData1 = b1->GetUserData();
	if (!userData1) {
		return;
	}

	void* userData2 = b2->GetUserData();
	if (!userData2) {
		return;
	}

	entity2 = static_cast<Entity*>(userData2);
	entity1 = static_cast<Entity*>(userData1);

	//alert them that they collided with each other
	entity1->collidedWith(entity2, world);
	entity2->collidedWith(entity1, world);

	//if either entity is the player, it's game over
	if (entity1 == player || entity2 == player) {
		player = NULL;
		std::cout << "game over" << endl;
	}

	audio.playExplosion();
}

void Model::EndContact(b2Contact* contact){


}

void Model::fire(){
	if (player != NULL) {
		b2Body* ship2 = this->player->getBody();
		uint32 currentTime = SDL_GetTicks();
		int delta = currentTime-weaponLastFired;
		if(delta > WEAPON_COOLDOWN){
			b2Vec2 loc = ship2->GetPosition();
			b2Vec2 offset = ship2->GetWorldVector(b2Vec2(0, -1));
			world->addProjectile(1, loc.x + (offset.x * 5), loc.y + (offset.y * 5), b2Vec2(offset.x * 500, offset.y * 500));
			weaponLastFired = currentTime;
			audio.playLaser();
		}
	}
}

bool Model::isPlayerAlive() {
	return this->player != NULL;
}

void Model::accelerate(int delta) {
	if (player != NULL) {
		b2Body* ship2 = this->player->getBody();
		b2Vec2 speed(0, delta * 150);
		b2Vec2 force = ship2->GetWorldVector(speed);
		ship2->ApplyForce(force, ship2->GetWorldCenter(), true);
	}
}

void Model::turn(int direction) {
	if (player != NULL) {
		b2Body* ship2 = this->player->getBody();
		float w = ship2->GetAngularVelocity();
		w += (direction * 0.5);

		if (w > 2) w = 2;
		if (w < -2) w = -2;

		ship2->SetAngularVelocity(w);
	}
}
