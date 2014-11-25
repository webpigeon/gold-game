/*
 * Bullet.cpp
 *
 *  Created on: 23 Nov 2014
 *      Author: webpigeon
 */

#include "Bullet.h"
#include <iostream>

//Bullet::Bullet() {
	// TODO Auto-generated constructor stub

//}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::collidedWith(Entity* entity, Manager<Entity>* manager) {
	std::cout << "I AM A BULLET! RAWR" << std::endl;
	manager->remove(this);
}

int Bullet::getEntityType() {
	//return ENTITY_TYPE;
}

