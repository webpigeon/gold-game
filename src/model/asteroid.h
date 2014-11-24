/*
 * asteroid.h
 *
 *  Created on: 18 Nov 2014
 *      Author: piers
 */

#ifndef ASTEROID_H_
#define ASTEROID_H_
#include "Entity.h"


class Asteroid : public Entity {
public:
	Asteroid(b2Body* body);
	int getEntityType();
};

//utility (factory) functions
b2BodyDef* buildAsteroidBodyDef(int sides, int size);
b2FixtureDef* buildAsteroidFixtureDef(int x, int y);


#endif /* ASTEROID_H_ */
