/*
 * world.cpp

 *
 *  Created on: 18 Nov 2014
 *      Author: piers
 */

#include "world.h"

World::World(){
	gravity = new b2Vec2(0.0f, 0.0f);
	physicsWorld = new b2World(*gravity);
}




