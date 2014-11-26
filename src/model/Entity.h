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

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <Box2D/Box2D.h>

#include "Manager.h"

class Entity {
	public:
		Entity(b2Body* body);
		virtual ~Entity();
		virtual void init();
		virtual void draw(SDL_GLContext* context);
		virtual void collidedWith(Entity* entity, Manager<Entity>* manager);
		virtual int getEntityType();
		b2Body* getBody();

	protected:
		b2Body* body;
};

#endif /* ENTITY_H_ */
