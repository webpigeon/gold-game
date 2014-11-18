/*
 * world.h
 *
 *  Created on: 18 Nov 2014
 *      Author: piers
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <Box2D/Box2D.h>
#include "asteroid.h"

class World {
	private:
		b2Vec2* gravity;
		b2World* physicsWorld;
	public:
		World();
};




#endif /* WORLD_H_ */
