/*
 * Projectile.h
 *
 *  Created on: 23 Nov 2014
 *      Author: piers
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "Entity.h"

class Projectile: public Entity {
public:
	Projectile(b2Body* body);
	virtual ~Projectile();
};

b2BodyDef* buildProjectileBodyDef(int x, int y);
b2FixtureDef* buildProjectileFixtureDef(int size);

#endif /* PROJECTILE_H_ */
