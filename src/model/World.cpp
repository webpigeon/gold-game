/*
 * world.cpp

 *
 *  Created on: 18 Nov 2014
 *      Author: piers
 */
#include "World.h"
#include "Turret.h"

#include <iostream>

#define VEL_INTER 8
#define POS_INTER 3
#define DELTA_PER_SEC 1000.0

World::World(){
	b2Vec2 gravity(0.0f, 0.0f);
	physicsWorld = new b2World(gravity);

}

void World::addColliderCallback(b2ContactListener* callback) {
	physicsWorld->SetContactListener(callback);
}

void World::update(int delta) {
	physicsWorld->Step(delta/DELTA_PER_SEC, VEL_INTER, POS_INTER);

	// Update everything
	for(vector<Entity*>::iterator itr = entities.begin(); itr != entities.end(); ++itr){
		(*itr)->update(delta, this);
	}

	// add any new entities
	std::set<Entity*>::iterator addIt = addList.begin();
	std::set<Entity*>::iterator addEnd = addList.end();
	for (; addIt!=addEnd; ++addIt) {
		Entity* entity = *addIt;
		entity->init(this);
		this->entities.push_back(entity);
	}
	addList.clear();

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
	addList.insert(entity);
}

vector<Entity*>* World::inRange(b2Vec2 location, float32 range){
	vector<Entity*>* results = new vector<Entity*>();
	for(vector<Entity*>::iterator itr = entities.begin(); itr != entities.end(); ++itr){
		b2Vec2 entLoc = (*itr)->getBody()->GetWorldCenter();

		if(!(entLoc.x == location.x && entLoc.y == location.y)){
			float32 distance = std::sqrt(std::pow(entLoc.x - location.x, 2) + std::pow(entLoc.y - location.y, 2));

			if((*itr)->getEntityType() == ENT_TYPE_SHIP){
//				cout << "Ship is: " << distance << " things away" << endl;
//				cout << entLoc.x << ":" << entLoc.y << " Is far away: " << distance << endl;
			}
			if(distance <= range){
				results->push_back(*itr);
//				cout << entLoc.x << ":" << entLoc.y << " Is far away: " << distance << endl;
			}
		}
	}
	return results;
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
	Ship* ship = new Ship(x, y, 1);
	add(ship);

	return ship;
}
