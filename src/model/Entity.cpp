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

void Entity::draw(SDL_GLContext* context){
	// TODO Draw the entity here please

	glBegin(GL_POLYGON);

	glVertex2f( 0, 0 );
	glVertex2f( 100, 100);
	glVertex2f( 200, 0);

	glEnd();
}

