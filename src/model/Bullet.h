/*
 * Bullet.h
 *
 *  Created on: 23 Nov 2014
 *      Author: webpigeon
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "Entity.h"

class Bullet: public Entity {
public:
	Bullet();
	virtual ~Bullet();
	int getEntityType();
};

#endif /* BULLET_H_ */
