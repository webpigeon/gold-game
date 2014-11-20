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
#include <vector>


using namespace std;

class World {
	private:
		b2World* physicsWorld;
		vector<Asteroid> asteroids;
	public:
		World();
		void draw(void);
};


#endif /* WORLD_H_ */
