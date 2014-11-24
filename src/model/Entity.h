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

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <Box2D/Box2D.h>

class Entity {
	public:
		Entity(b2Body* body);
		virtual ~Entity();
		virtual void draw(SDL_GLContext* context);
		virtual int getEntityType();

	protected:
		b2Body* body;
};

#endif /* ENTITY_H_ */
