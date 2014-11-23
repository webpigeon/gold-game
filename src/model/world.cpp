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
		addAsteroid(8, 40, i * 150, i * 150);
	}
	addProjectile(5, 25, 25);

	addShip(50, 50);
}

void World::update(int delta) {
	//std::cout << "delta: " << delta / DELTA_PER_SEC << std::endl;
	physicsWorld->Step(delta/DELTA_PER_SEC, VEL_INTER, POS_INTER);
}

void World::draw(SDL_GLContext* context){
	for(uint i = 0; i < entities.size(); i++){
		entities[i].draw(context);
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
	this->entities.push_back(*temp);

	//TODO find out if it's safe to delete fixture and bodydef here
}

void World::accelerate(int delta) {

}

void World::turn(int direction) {

}

void World::addShip(float32 x, float32 y){
	b2FixtureDef* fixture = buildShipFixtureDef();
	b2BodyDef* bodyDef = buildShipBodyDef(x, y);
	b2Body* body = physicsWorld -> CreateBody(bodyDef);
	body -> CreateFixture(fixture);
	Ship* temp = new Ship(body);
	this -> entities.push_back(*temp);
}

void World::addProjectile(float32 size, float32 x, float32 y){
	b2FixtureDef* fixture = buildProjectileFixtureDef(size);
	b2BodyDef* bodyDef = buildProjectileBodyDef(x, y);
	b2Body* body = physicsWorld -> CreateBody(bodyDef);
	body -> CreateFixture(fixture);
	Projectile* temp = new Projectile(body);
	this -> entities.push_back(*temp);
}



