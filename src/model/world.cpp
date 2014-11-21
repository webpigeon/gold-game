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
		addAsteroid(5, 40, i * 50, i * 50);
	}

}

void World::draw(){
	for(uint i = 0; i < asteroids.size(); i++){
		asteroids[i].draw();
	}
}

void World::addAsteroid(int points, float32 roughSize, float32 x, float32 y){
	Asteroid* temp = new Asteroid(points, roughSize, x, y);

	// TODO - Joe is there an easier way to do this lol? this code is horrible looking
	temp -> insertBody(physicsWorld -> CreateBody(&(temp -> getBodyDef())));
	this -> asteroids.push_back(*temp);
}



