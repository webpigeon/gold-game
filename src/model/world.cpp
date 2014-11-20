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
		Asteroid* temp = new Asteroid(4, 40, b2Vec2(i * 50, i * 50));
		this -> asteroids.push_back(*temp);
	}

}

void World::draw(){
}



