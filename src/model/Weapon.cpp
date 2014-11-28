/*
 * Weapon.cpp
 *
 *  Created on: 27 Nov 2014
 *      Author: piers
 */

#include "Weapon.h"

Weapon::Weapon(float sizeOfShip) {
	// TODO Auto-generated constructor stub
	range = 35;
	heat = 0;

	coolPerSecond = 5;
	heatFromFiring = 25;
	maxHeat = 110;
	minHeat = 15;
	cooling = false;
	canFire = true;
	tooHot = false;
	delayed = false;
	shotDelay = 250;
	msTillWeCanShoot = 0;
	damagePerProjectile = 100;
	sizeOfProjectile = 0.50;
	size = sizeOfShip;
}

Weapon::~Weapon() {
	// TODO Auto-generated destructor stub
}

float Weapon::getRange(){
	return range;
}

float Weapon::getHeat(){
	return heat;
}

void Weapon::setRange(float range){
	this->range = range;
}
void Weapon::setCoolPerSecond(int coolPerSecond){
	this->coolPerSecond = coolPerSecond;
}
void Weapon::setHeatFromFiring(int heatFromFiring){
	this->heatFromFiring = heatFromFiring;
}
void Weapon::setMaxHeat(int maxHeat){
	this->maxHeat = maxHeat;
}
void Weapon::setMinHeat(int minHeat){
	this->minHeat = minHeat;
}
void Weapon::setShotDelay(int shotDelay){
	this->shotDelay = shotDelay;
}
void Weapon::setDamagePerProjectile(float damagePerProjectile){
	this->damagePerProjectile = damagePerProjectile;
}
void Weapon::setSizeOfProjectile(float sizeOfProjectile){
	this->sizeOfProjectile = sizeOfProjectile;
}

void Weapon::update(int delta, Manager<Entity>* manager, b2Body* body){
	calcCooldown(delta);
	calcShotDelay(delta);

	canFire = !(delayed || tooHot);
	if(canFire){
		// Fire at something if its in range

		b2Vec2 location = body->GetWorldCenter();
		vector<Entity*>* inRange = manager->inRange(location, range);

		if(inRange->size() >= 1){
			float minDistance = range + 1;
			Entity* minEntity = NULL;
			for(vector<Entity*>::iterator  itr = inRange->begin(); itr != inRange->end(); ++itr){
				if((*itr)->getEntityType() == ENT_TYPE_SHIP){
					b2Vec2 entLoc = (*itr)->getBody()->GetWorldCenter();
					float32 distance = sqrt(pow(entLoc.x - location.x, 2) + pow(entLoc.y - location.y, 2));
					if(distance < minDistance){
						minDistance = distance;
						minEntity = (*itr);
					}
				}
			}
			if(minEntity != NULL){
				b2Vec2 loc = body->GetWorldCenter();

				b2Vec2 target = (minEntity->getBody()->GetPosition());
				target.x *= 1 + (rand() % 2 - 1)/20.0f;
				target.y *= 1 + (rand() % 2 - 1)/20.0f;
				target -= loc;
				target.Normalize();

				b2Vec2 position(loc.x + (target.x*(size+1)), loc.y + (target.y*(size+1)));

				b2Vec2 speed(target.x * 250, target.y * 250);
				Projectile* proj = new Projectile(position.x, position.y,speed, sizeOfProjectile, damagePerProjectile);
				manager->add(proj);
				heat+=heatFromFiring;
				msTillWeCanShoot += shotDelay;
			}
		}
	}
}

void Weapon::calcCooldown(int delta){
	if(cooling){
		heat -= (coolPerSecond / 1000.0f) * delta;
		if(heat <= 0){
			heat = 0;
			cooling = false;
		}
		if(tooHot && heat <= minHeat){
			tooHot = false;
			cout << "Turret cooled down" << endl;
		}
	}

	if(heat > 0){
		cooling = true;
	}

	// Regardless of cooling state , must not fire after this point
	if(heat >= maxHeat){
		tooHot = true;
		cout << "Turret too  hot" << endl;
	}
}

void Weapon::calcShotDelay(int delta){
	if(msTillWeCanShoot > 0) delayed = true;
	if(delayed){
		msTillWeCanShoot -= delta;

		if(msTillWeCanShoot <= 0){
			msTillWeCanShoot = 0;
			delayed = false;
		}
	}
}
