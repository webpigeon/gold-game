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
	Wall(float32 x, float32 y, float32 size, bool distructable=false);
	void init(Manager<Entity>* manager);
	virtual ~Wall();
	int getEntityType();
	void collidedWith(Entity* entity, Manager<Entity>* manager);

private:
	bool distructable;
};

b2FixtureDef* buildWallFixtureDef(float32 size);
b2BodyDef* buildWallBodyDef(float32 x, float32 y);
b2PolygonShape* buildProjectileShape(float32 size);

#endif /* WALL_H_ */
