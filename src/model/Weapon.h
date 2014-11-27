/*
 * Weapon.h
 *
 *  Created on: 27 Nov 2014
 *      Author: piers
 */

#ifndef WEAPON_H_
#define WEAPON_H_

#include <vector>
#include "Entity.h"
#include <iostream>
#include "Projectile.h"

using namespace std;

class Weapon {
public:
	Weapon(float sizeOfShip);
	virtual ~Weapon();
	void update(int delta, Manager<Entity>* manager, b2Body* body);
	float getHeat();
	float getRange();
	void setRange(float range);
	void setCoolPerSecond(int coolPerSecond);
	void setHeatFromFiring(int heatFromFiring);
	void setMaxHeat(int maxHeat);
	void setMinHeat(int minHeat);
	void setShotDelay(int shotDelay);
	void setDamagePerProjectile(float damagePerProjectile);
	void setSizeOfProjectile(float sizeOfProjectile);


protected:
	float range; // Radius of range of turret in meters
	int heat; // How hot are we?
	int coolPerSecond; // How much do we cooldown a second
	int heatFromFiring; // How hot do we get when firing
	int maxHeat; // How hot can we be before stopping to fire
	int minHeat; // When do we stop cooling down and can fire again
	bool cooling; // Are we cooling down?
	bool tooHot; // are we too hot to fire?
	bool canFire; // Can we fire if there were something to shoot at?
	bool delayed; // Are we waiting for shot delay
	int shotDelay; // delay between shots in ms
	int msTillWeCanShoot; // How long till we can shoot again in ms
	float damagePerProjectile;
	float sizeOfProjectile;
	float size;

	void calcCooldown(int delta);
	void calcShotDelay(int delta);
};

#endif /* WEAPON_H_ */
