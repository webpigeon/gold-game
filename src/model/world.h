/*
 * world.h
 *
 *  Created on: 18 Nov 2014
 *      Author: piers
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <Box2D/Box2D.h>


class World {
	private:
		b2World* physicsWorld;
	public:
		World();
		void draw(void);
};


#endif /* WORLD_H_ */
