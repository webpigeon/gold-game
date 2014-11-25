/*
 * Turret.cpp
 *
 *  Created on: 25 Nov 2014
 *      Author: piers
 */

#include "Turret.h"

Turret::Turret(b2Body* body) : Entity(body) {
	// TODO Auto-generated constructor stub
	range = 35;
	heat = 0;
	coolPerSecond = 10;
	heatFromFiring = 25;
	maxHeat = 110;
	minHeat = 35;
	cooling = false;
	canFire = true;
}

void Turret::update(int delta, Manager<Entity>* manager){
	calcCooldown(delta);
	if(canFire){
		// Fire at something if its in range
	}
}

void Turret::calcCooldown(int delta){
	if(cooling){
		heat -= (coolPerSecond * delta) / 1000.0f;
		if(heat <= 0){
			heat = 0;
		}
		if(heat <= 35){
			cooling = false;
			canFire = true;
		}
	}else{
		if(heat > 0){
			cooling = true;
		}
	}

	// Regardless of cooling state , must not fire after this point
	if(heat >= maxHeat){
		canFire = false;
	}
}

Turret::~Turret() {
	// TODO Auto-generated destructor stub
}

