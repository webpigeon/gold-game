/*
 * world.cpp

 *
 *  Created on: 18 Nov 2014
 *      Author: piers
 */

#include "world.h"
#include <iostream>

#define VEL_INTER 8
#define POS_INTER 3
#define DELTA_PER_SEC 1000.0

World::World(){
	b2Vec2 gravity(0.0f, 0.0f);
	physicsWorld = new b2World(gravity);

	//addWall(5, 20, 20);
	//addWall(5, 20, 30);
}

void World::addColliderCallback(b2ContactListener* callback) {
	physicsWorld->SetContactListener(callback);
}

void World::update(int delta) {
	physicsWorld->Step(delta/DELTA_PER_SEC, VEL_INTER, POS_INTER);

	//kill all dead entities
	std::set<Entity*>::iterator it = killList.begin();
	std::set<Entity*>::iterator end = killList.end();
	for (; it!=end; ++it) {
		Entity* entity = *it;

		std::vector<Entity*>::iterator deleteIt = std::find(entities.begin(), entities.end(), entity);
		if (deleteIt != entities.end()) {
			entities.erase(deleteIt);
		}

		delete entity;
	}

	killList.clear();
}

void World::draw(){
	glMatrixMode(GL_MODELVIEW);

	std::vector<Entity*>::iterator it = entities.begin();
	std::vector<Entity*>::iterator end = entities.end();
	for (; it!=end; ++it) {
		Entity* entity = *it;
		entity->draw();
	}
}

void World::add(Entity* entity) {
	entity->init();
	this->entities.push_back(entity);
}

void World::remove(Entity* entity) {
	killList.insert(entity);
}

b2Body* World::buildBody(b2FixtureDef* fixture, b2BodyDef* bodyDef){
	b2Body* body = physicsWorld -> CreateBody(bodyDef);
	body -> CreateFixture(fixture);
	return body;
}

b2Body* World::buildBody(b2BodyDef* bodyDef){
	b2Body* body = physicsWorld -> CreateBody(bodyDef);
	return body;
}

Entity* World::addShip(float32 x, float32 y){
	b2Body* body = buildBody(buildShipBodyDef(x, y));
	Ship* ship = new Ship(body);
	add(ship);

	return ship;
}



