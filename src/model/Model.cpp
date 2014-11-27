/*
 * Model.cpp
 *
 *  Created on: 23 Nov 2014
 *      Author: webpigeon
 */

#include "Model.h"
#include "Entity.h"
#include "Projectile.h"
#include <iostream>

#define WEAPON_COOLDOWN 500

using namespace std;

Model::Model(World* world, Entity* player) {
	this->world = world;
	this->score = 0;
	this->player = player;
	this->weaponLastFired = 0;
	this->goalsLeft = 1;
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
		if(player->getHealth() <= 0){
			player = NULL;
			std::cout << "game over" << endl;
		}
	}

	if (entity1->getEntityType() == ENT_TYPE_GOAL && entity2->getEntityType() == ENT_TYPE_BULLET) {
		player = NULL;
		goalsLeft--;
		std::cout << "You win!" << std::endl;
	}

	if (entity2->getEntityType() == ENT_TYPE_BULLET && entity1->getEntityType() == ENT_TYPE_ASTEROID) {
		score += 1;
		audio.playExplosion();
	}
}

void Model::EndContact(b2Contact* contact){


}

void Model::fire(){
	if (isPlayerAlive()) {
		b2Body* ship2 = this->player->getBody();
		uint32 currentTime = SDL_GetTicks();
		int delta = currentTime-weaponLastFired;
		if(delta > WEAPON_COOLDOWN){
			b2Vec2 loc = ship2->GetPosition();
			b2Vec2 offset = ship2->GetWorldVector(b2Vec2(0, -1));

			b2Vec2 location(loc.x + (offset.x * 5), loc.y + (offset.y * 5));
			b2Vec2 speed(offset.x * 500, offset.y * 500);

			Projectile* proj = new Projectile(location.x, location.y, speed, 0.5);
			world->add(proj);

			weaponLastFired = currentTime;
			audio.playLaser();
		}
	}
}

bool Model::hasPlayerWon() {
	return goalsLeft == 0;
}

bool Model::isPlayerAlive() {
	return player != NULL && player->getBody() != NULL;
}

int Model::getScore() {
	return this->score;
}

void Model::accelerate(int delta) {
	if (isPlayerAlive()) {
		b2Body* ship2 = this->player->getBody();
		b2Vec2 speed(0, delta * 150);
		b2Vec2 force = ship2->GetWorldVector(speed);
		ship2->ApplyForce(force, ship2->GetWorldCenter(), true);
	}
}

void Model::turn(int direction) {
	if (isPlayerAlive()) {
		b2Body* ship2 = this->player->getBody();
		float w = ship2->GetAngularVelocity();
		w += (direction * 0.5);

		if (w > 2) w = 2;
		if (w < -2) w = -2;

		ship2->SetAngularVelocity(w);
	}
}
