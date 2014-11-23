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
	Ship(b2Body* body);
};

b2FixtureDef* buildShipFixtureDef();
b2BodyDef* buildShipBodyDef(int x, int y);

#endif /* SHIP_H_ */