/*
 * world.cpp

 *
 *  Created on: 18 Nov 2014
 *      Author: piers
 */

#include "world.h"

World::World(){
	b2Vec2 gravity(0.0f, 0.0f);
	physicsWorld = new b2World(gravity);

	for(int i = 1; i < 5; i++){
		addAsteroid(4, 40, i * 50, i * 50);
	}

}

void World::draw(){
}

void World::addAsteroid(int points, float32 roughSize, float32 x, float32 y){
	Asteroid* temp = new Asteroid(4, 40, x, y);
	this -> asteroids.push_back(*temp);
}



