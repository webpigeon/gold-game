/*
 * Turret.h
 *
 *  Created on: 25 Nov 2014
 *      Author: piers
 */

#ifndef TURRET_H_
#define TURRET_H_

#include "Entity.h"

class Turret: public Entity {
public:
	Turret(b2Body* body);
	virtual ~Turret();
	void update(int delta, Manager<Entity>* manager);

private:
	float range; // Radius of range of turret in meters
	float heat; // How hot are we?
	float coolPerSecond; // How much do we cooldown a second
	float heatFromFiring; // How hot do we get when firing
	float maxHeat; // How hot can we be before stopping to fire
	float minHeat; // When do we stop cooling down and can fire again
	bool cooling;
	bool canFire;

	void calcCooldown(int delta);

};

#endif /* TURRET_H_ */
