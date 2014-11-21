/*
 * Entity.cpp
 *
 *  Created on: 19 Nov 2014
 *      Author: piers
 */

#include "Entity.h"
#include <iostream>

Entity::Entity() {
	// TODO Auto-generated constructor stub

}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

void Entity::draw(SDL_Renderer* renderer){
	// TODO Draw the entity here please

	Sint16 vx[] = {0, 100, 200};
	Sint16 vy[] = {0, 100, 0};
	int sides = 3;

	int r = 255;
	int g = 255;
	int b = 255;
	int a = 255;

	polygonRGBA(renderer, vx, vy, sides, r, g, b, a);
}

