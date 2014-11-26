/*
 * Wall.h
 *
 *  Created on: 24 Nov 2014
 *      Author: piers
 */

#ifndef WALL_H_
#define WALL_H_

#include "Entity.h"

class Wall : public Entity {
public:
	Wall(b2Body* body, float32 size);
	virtual ~Wall();
	int getEntityType();
};

b2FixtureDef* buildWallFixtureDef(float32 size);
b2BodyDef* buildWallBodyDef(float32 x, float32 y);
b2PolygonShape* buildProjectileShape(float32 size);

#endif /* WALL_H_ */
