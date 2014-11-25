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

		//addAsteroid(8, 4, x, y);
	}

	//addWall(5, 20, 20);
	//addWall(5, 20, 30);
}

void World::addColliderCallback(b2ContactListener* callback) {
	physicsWorld->SetContactListener(callback);
}

void World::update(int delta) {
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

void World::add(Entity* entity) {
	this->entities.push_back(entity);
}

void World::remove(Entity* entity) {
	killList.push_back(entity);
}

b2Body* World::buildBody(b2FixtureDef* fixture, b2BodyDef* bodyDef){
	b2Body* body = physicsWorld -> CreateBody(bodyDef);
	body -> CreateFixture(fixture);
	return body;
}

void World::addAsteroid(int points, float32 roughSize, float32 x, float32 y){
	b2Body* body = buildBody(buildAsteroidFixtureDef(points, roughSize), buildAsteroidBodyDef(x, y));
	Asteroid* asteroid = new Asteroid(body);
	add(asteroid);
}

Entity* World::addShip(float32 x, float32 y){
	b2Body* body = buildBody(buildShipFixtureDef(), buildShipBodyDef(x, y));
	Ship* ship = new Ship(body);
	add(ship);
	return ship;
}

void World::addProjectile(float32 size, float32 x, float32 y, b2Vec2 initialVelocity){
	b2Body* body = buildBody(buildProjectileFixtureDef(size), buildProjectileBodyDef(x, y));
	Projectile* projectile = new Projectile(body, initialVelocity);
	add(projectile);
}

void World::addWall(float32 size, float32 x, float32 y){
	b2Body* body = buildBody(buildWallFixtureDef(size), buildWallBodyDef(x, y));
	Wall* wall = new Wall(body);
	add(wall);
}



