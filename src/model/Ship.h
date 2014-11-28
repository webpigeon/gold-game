/*
 * Ship.h
 *
 *  Created on: 23 Nov 2014
 *      Author: piers
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "Entity.h"

class Ship: public Entity {
public:
	Ship(float32 x, float32 y, float32 size);
	void init(Manager<Entity>* manager);
	void update(int delta, Manager<Entity>* manager);
	b2Body* getBody();
	int getEntityType();
};

b2FixtureDef* buildShipFixtureDef();
b2BodyDef* buildShipBodyDef(int x, int y);

#endif /* SHIP_H_ */
