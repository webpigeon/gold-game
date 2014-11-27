/*
 * Entity.h
 *
 *  Created on: 19 Nov 2014
 *      Author: piers
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#define ENT_TYPE_UNDEFINED 0
#define ENT_TYPE_ASTEROID 1
#define ENT_TYPE_SHIP 2
#define ENT_TYPE_BULLET 3
#define ENT_TYPE_WALL 4
#define ENT_TYPE_TURRET 5
#define ENT_TYPE_TURRET_SENSOR 6
#define ENT_TYPE_GOAL 7

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <Box2D/Box2D.h>

#include "Manager.h"

class Entity {
	public:
		Entity(float32 x, float32 y, float32 size);
		virtual ~Entity();
		virtual void init(Manager<Entity>* manager) = 0;
		virtual void update(int delta, Manager<Entity>* manager);
		virtual void draw();
		virtual void collidedWith(Entity* entity, Manager<Entity>* manager);
		virtual int getEntityType();
		b2Body* getBody();
		float getHealth();

	protected:
		b2Body* body;
		b2Vec2 initPos;
		float32 size;
		float health;
		float color[3];
};

#endif /* ENTITY_H_ */
