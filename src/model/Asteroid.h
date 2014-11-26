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
	Asteroid(b2Body* body, float32 size);
	void collidedWith(Entity* entity, Manager<Entity>* manager);
	int getEntityType();
};

//utility (factory) functions
b2BodyDef* buildAsteroidBodyDef(int x, int y);
b2FixtureDef* buildAsteroidFixtureDef(float32 size);


#endif /* ASTEROID_H_ */
