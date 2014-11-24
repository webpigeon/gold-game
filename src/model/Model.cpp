/*
 * Model.cpp
 *
 *  Created on: 23 Nov 2014
 *      Author: webpigeon
 */

#include "Model.h"
#include "Entity.h"
#include <iostream>

using namespace std;

Model::Model(World* world) {
	this->world = world;
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
	if (entity1->getEntityType() != entity2->getEntityType()) {
		world->remove(entity1);
		world->remove(entity2);
	}

	std::cout << "collision detected " << entity1->getEntityType() << "," << entity2->getEntityType() << std::endl;
	audio.playExplosion();
}

void Model::EndContact(b2Contact* contact){


}
