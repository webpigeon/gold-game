/*
 * Entity.h
 *
 *  Created on: 19 Nov 2014
 *      Author: piers
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

class Entity {
public:
	Entity();
	virtual ~Entity();

	virtual void draw(SDL_Renderer* renderer);
};

#endif /* ENTITY_H_ */
