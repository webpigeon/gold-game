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

	addTurret(4, 35, 35, 800);
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

	//kill all dead entities
	std::set<Entity*>::iterator it = killList.begin();
	std::set<Entity*>::iterator end = killList.end();
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

vector<Entity*>* World::inRange(b2Vec2 location, float32 range, Entity* nearest){
	vector<Entity*>* results = new vector<Entity*>();

	float32 minDistance = range+1;
	Entity* minEntity;
	for(vector<Entity*>::iterator itr = entities.begin(); itr != entities.end(); ++itr){
		b2Vec2 entLoc = (*itr)->getBody()->GetPosition();
		float32 distance = std::sqrt(std::pow(entLoc.x + location.x, 2) + std::pow(entLoc.y + location.y, 2));
		if(distance <= range){
			results->push_back(*itr);
			if(distance < minDistance){
				minEntity = (*itr);
				minDistance = distance;
			}
		}
	}

	nearest = minEntity;
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

void World::addAsteroid(int points, float32 roughSize, float32 x, float32 y){
	b2Body* body = buildBody(buildAsteroidFixtureDef(points, roughSize), buildAsteroidBodyDef(x, y));
	Asteroid* asteroid = new Asteroid(body);
	add(asteroid);
}

Entity* World::addShip(float32 x, float32 y){
	b2Body* body = buildBody(buildShipFixtureDef(), buildShipBodyDef(x, y));
	Ship* ship = new Ship(body);
	add(ship);

	ship->init();
	return ship;
}

void World::addProjectile(float32 size, float32 x, float32 y, b2Vec2 initialVelocity){
	b2Body* body = buildBody(buildProjectileBodyDef(x, y));
	Projectile* projectile = new Projectile(body, initialVelocity, size);
	add(projectile);
}

void World::addWall(float32 size, float32 x, float32 y){
	b2Body* body = buildBody(buildWallFixtureDef(size), buildWallBodyDef(x, y));
	Wall* wall = new Wall(body);
	add(wall);
}

void World::addTurret(float32 size, float32 x, float32 y, float32 radius){
	b2Body* turretBody = buildBody(buildTurretFixtureDef(size), buildTurretBodyDef(x, y));
	Turret* turret = new Turret(turretBody);
	add(turret);
}



