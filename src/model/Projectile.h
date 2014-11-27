/*
 * Projectile.h
 *
 *  Created on: 23 Nov 2014
 *      Author: piers
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "Entity.h"

class Projectile: public Entity {
public:
	Projectile(float32 x, float32 y, b2Vec2 initialVelocity, float32 size, float32 damage = 100);
	void init(Manager<Entity>* manager);
	virtual ~Projectile();
	void update(int delta, Manager<Entity>* manager);
	void collidedWith(Entity* entity, Manager<Entity>* manager);
	void draw();
	int getEntityType();
private:
	b2Vec2 initVelocity;
	int pointsLength;
	b2Vec2* pointsArray;
	void generatePoints();
	bool generated;
	float32 damage;
	float32 getHealth();
};

b2BodyDef* buildProjectileBodyDef(float32 x, float32 y);
b2FixtureDef* buildProjectileFixtureDef(float32 size);

#endif /* PROJECTILE_H_ */
