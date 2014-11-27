/*
 * Turret.h
 *
 *  Created on: 25 Nov 2014
 *      Author: piers
 */

#ifndef TURRET_H_
#define TURRET_H_

#include "Entity.h"
#include <vector>
#include <iostream>
#include "Projectile.h"
#include "Weapon.h"

using namespace std;

class Turret: public Entity {
public:
	Turret(float32 x, float32 y, float32 size);
	void init(Manager<Entity>* manager);
	virtual ~Turret();
	void update(int delta, Manager<Entity>* manager);
	int getEntityType();
	float getRange();

protected:
	Weapon weapon;
};

b2BodyDef* buildTurretBodyDef(int x, int y);
b2FixtureDef* buildTurretFixtureDef(int size);

class TurretMiniGun : public Turret{
public:
	TurretMiniGun(float32 x, float32 y, float32 size);
};


#endif /* TURRET_H_ */
