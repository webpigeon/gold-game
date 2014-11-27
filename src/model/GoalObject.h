/*
 * GoalObject.h
 *
 *  Created on: 27 Nov 2014
 *      Author: webpigeon
 */

#ifndef GOALOBJECT_H_
#define GOALOBJECT_H_

#include "Entity.h"

class GoalObject : public Entity {
public:
	GoalObject(float32 x, float32 y, float32 size);
	void init(Manager<Entity>* manager);
	void collidedWith(Entity* entity, Manager<Entity>* manager);
	int getEntityType();
	virtual ~GoalObject();
};

#endif /* GOALOBJECT_H_ */
