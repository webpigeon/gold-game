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

	for(int i = 1; i < 5; i++){
		int x = rand() % 80;
		int y = rand() % 60;

		addAsteroid(8, 4, x, y);
	}

	addWall(5, 20, 20);
	addWall(5, 20, 30);
}

void World::addColliderCallback(b2ContactListener* callback) {
	physicsWorld->SetContactListener(callback);
}

void World::update(int delta) {
	//std::cout << "delta: " << delta / DELTA_PER_SEC << std::endl;
	physicsWorld->Step(delta/DELTA_PER_SEC, VEL_INTER, POS_INTER);

	//kill all dead entities
	std::vector<Entity*>::iterator it = killList.begin();
	std::vector<Entity*>::iterator end = killList.end();
	for (; it!=end; ++it) {
		Entity* entity = *it;

		std::vector<Entity*>::iterator it = std::find(entities.begin(), entities.end(), entity);
		if (it != entities.end()) {
			entities.erase(it);
		}

		delete entity;
	}

	killList.clear();
}

void World::draw(SDL_GLContext* context){
	glMatrixMode(GL_MODELVIEW);

	std::vector<Entity*>::iterator it = entities.begin();
	std::vector<Entity*>::iterator end = entities.end();
	for (; it!=end; ++it) {
		Entity* entity = *it;
		entity->draw(context);
	}
}

void World::addAsteroid(int points, float32 roughSize, float32 x, float32 y){
	//create the required components
	b2FixtureDef* fixture = buildAsteroidFixtureDef(points, roughSize);
	b2BodyDef* bodyDef = buildAsteroidBodyDef(x, y);

	//create the asteroid and add it
	b2Body* body = physicsWorld->CreateBody(bodyDef);
	body->CreateFixture(fixture);
	Asteroid* temp = new Asteroid(body);
	this->entities.push_back(temp);

	//TODO find out if it's safe to delete fixture and bodydef here
}

void World::add(Entity* entity) {
	this->entities.push_back(entity);
}

void World::remove(Entity* entity) {
	killList.push_back(entity);
}

Entity* World::addShip(float32 x, float32 y){
	b2FixtureDef* fixture = buildShipFixtureDef();
	b2BodyDef* bodyDef = buildShipBodyDef(x, y);
	b2Body* body = physicsWorld -> CreateBody(bodyDef);
	body -> CreateFixture(fixture);
	Ship* temp = new Ship(body);
	this->entities.push_back(temp);

	return temp;
}

Entity* World::addBullet(float32 x, float32 y, float32 angle) {
	b2FixtureDef* fixture = buildShipFixtureDef();
	b2BodyDef* bodyDef = buildShipBodyDef(x, y);
	bodyDef->bullet = true;
	bodyDef->angle = angle;

	b2Body* body = physicsWorld->CreateBody(bodyDef);

	body->CreateFixture(fixture);
	Entity* tmp = new Entity(body);
	this->entities.push_back(tmp);

	return tmp;
}

void World::addProjectile(float32 size, float32 x, float32 y, b2Vec2 initialVelocity){
	b2FixtureDef* fixture = buildProjectileFixtureDef(size);
	b2BodyDef* bodyDef = buildProjectileBodyDef(x, y);
	b2Body* body = physicsWorld -> CreateBody(bodyDef);
	body -> CreateFixture(fixture);
	Projectile* temp = new Projectile(body, initialVelocity);
	this -> entities.push_back(temp);
}

void World::addWall(float32 size, float32 x, float32 y){
	b2FixtureDef* fixture = buildWallFixtureDef(size);
	b2BodyDef* bodyDef = buildWallBodyDef(x, y);
	b2Body* body = physicsWorld -> CreateBody(bodyDef);
	body -> CreateFixture(fixture);
	Wall* temp = new Wall(body);
	this   -> entities.push_back(temp);
}



