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

	//Walls should not die when stuff crashes into them
	if (entity1->getEntityType() == ENT_TYPE_WALL || entity2->getEntityType() == ENT_TYPE_WALL) {
		return;
	}

	if (entity1->getEntityType() != entity2->getEntityType()) {
		world->remove(entity1);
		world->remove(entity2);
	}

	if ( (entity1->getEntityType() == ENT_TYPE_BULLET && entity2->getEntityType()) == ENT_TYPE_ASTEROID || (entity2->getEntityType() == ENT_TYPE_BULLET && entity1->getEntityType() == ENT_TYPE_ASTEROID) ) {
		score += 1;
		std::cout << "score: " << score << std::endl;
	}

	std::cout << "collision detected " << entity1->getEntityType() << "," << entity2->getEntityType() << std::endl;
	audio.playExplosion();
}

void Model::EndContact(b2Contact* contact){


}

void Model::fire(){
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

void Model::accelerate(int delta) {
	b2Body* ship2 = this->player->getBody();
	b2Vec2 speed(0, delta * 150);
	b2Vec2 force = ship2->GetWorldVector(speed);
	ship2->ApplyForce(force, ship2->GetWorldCenter(), true);
}

void Model::turn(int direction) {
	b2Body* ship2 = this->player->getBody();
	float w = ship2->GetAngularVelocity();
	w += direction;

	if (w > 2) w = 2;
	if (w < -2) w = -2;

	ship2->SetAngularVelocity(w);
}
