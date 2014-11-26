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

using namespace std;

class Turret: public Entity {
public:
	Turret(b2Body* body);
	virtual ~Turret();
	void update(int delta, Manager<Entity>* manager);

private:
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

	void calcCooldown(int delta);
	void calcShotDelay(int delta);
};

b2BodyDef* buildTurretBodyDef(int x, int y);
b2FixtureDef* buildTurretFixtureDef(int size);

// Linked to a turret, spots things in range
class TurretRange : public Entity {
public:
	TurretRange(Turret* turret, b2Body* body);
	virtual ~TurretRange();
	void update(int delta, Manager<Entity>* manager);

	void collidedWith(Entity* entity, Manager<Entity>* manager);
private:
	vector<Entity> entitiesInRange;
	Turret* turret;
};

b2BodyDef* buildTurretRangeBodyDef(int x, int y);
b2FixtureDef* buildTurretRangeFixtureDef(int size);

#endif /* TURRET_H_ */
