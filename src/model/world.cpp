/*
 * world.cpp

 *
 *  Created on: 18 Nov 2014
 *      Author: piers
 */

#include "world.h"

#define VEL_INTER 8
#define POS_INTER 3
#define DELTA_PER_SEC 1000.0

World::World(){
	b2Vec2 gravity(0.0f, 0.0f);
	physicsWorld = new b2World(gravity);

	for(int i = 1; i < 5; i++){
		addAsteroid(8, 40, i * 100, i * 100);
	}
}

void World::update(int delta) {
	physicsWorld->Step(delta/DELTA_PER_SEC, VEL_INTER, POS_INTER);
}

void World::draw(SDL_Renderer* renderer){
	for(uint i = 0; i < asteroids.size(); i++){
		asteroids[i].draw(renderer);
	}
}

void World::addAsteroid(int points, float32 roughSize, float32 x, float32 y){
	Asteroid* temp = new Asteroid(points, roughSize, x, y);

	// TODO - Joe is there an easier way to do this lol? this code is horrible looking
	temp -> insertBody(physicsWorld -> CreateBody(&(temp -> getBodyDef())));
	this -> asteroids.push_back(*temp);
}



