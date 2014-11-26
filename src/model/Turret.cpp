/*
 * Turret.cpp
 *
 *  Created on: 25 Nov 2014
 *      Author: piers
 */

#include "Turret.h"
#include <cmath>

static b2PolygonShape* buildTurretShape(int points, int size);
static b2PolygonShape* buildTurretRangeShape(int points, int size);

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
	tooHot = false;
	delayed = false;
	shotDelay = 500;
	msTillWeCanShoot = 0;

	entitiesInRange = new vector<Entity>();
}

int Turret::getEntityType(){
	return ENT_TYPE_TURRET;
}

float Turret::getRange(){
	return range;
}

void Turret::update(int delta, Manager<Entity>* manager){
	calcCooldown(delta);
	calcShotDelay(delta);

	// Can fire if we are not delayed and not tooHot
	canFire = !(delayed || tooHot);
	if(canFire){
		// Fire at something if its in range
		Entity* nearest;
		vector<Entity*> inRange = manager->inRange(body->GetPosition(), range, *nearest);
		// fire at nearest;

	}
}

void Turret::collidedWith(Entity* entity, Manager<Entity>* manager){
	cout << "Turret collided with: " << entity->getEntityType() << endl;
}

void Turret::calcCooldown(int delta){
	if(cooling){
		heat -= (coolPerSecond * delta) / 1000.0f;
		if(heat <= 0){
			heat = 0;
		}
		if(heat <= 35){
			tooHot = false;
		}
	}

	if(heat > 0){
		cooling = true;
	}

	// Regardless of cooling state , must not fire after this point
	if(heat >= maxHeat){
		tooHot = true;
	}
}

void Turret::calcShotDelay(int delta){
	if(delayed){
		msTillWeCanShoot -= delta;

		if(msTillWeCanShoot <= 0){
			msTillWeCanShoot = 0;
			delayed = false;
		}
	}
}

Turret::~Turret() {
	// TODO Auto-generated destructor stub
}

b2FixtureDef* buildTurretFixtureDef(int size){
	b2FixtureDef* fixture = new b2FixtureDef();
	fixture->shape = buildTurretShape(8, size);
	fixture->density = 1.0f;
	fixture->friction = 0.0f;
	return fixture;
}

b2BodyDef* buildTurretBodyDef(int x, int y){
	b2BodyDef* bodyDef = new b2BodyDef();
	bodyDef->type=b2_staticBody;
	bodyDef->bullet = false; //TODO do we need to set this
	bodyDef->position.Set(x, y);
	return bodyDef;
}

b2PolygonShape* buildTurretShape(int points, int size){
	b2PolygonShape* shape = new b2PolygonShape();
	b2Vec2 pointsArray[points];

	float deg = 0;
	for(int i = 0; i < points; i++){
		float x = cos(2 * M_PI * i / points);
		float y = sin(2 * M_PI * i / points);

		pointsArray[i] = b2Vec2(x * size, y * size);
		deg += 360.0f / points;
	}

	shape->Set(pointsArray, points);
	return shape;
}

/**
 ************************************
 *********** TurretRange ************
 ************************************
 */

TurretRange::TurretRange(Turret* turret, b2Body* body) : Entity(body){
	this->turret = turret;
}

int TurretRange::getEntityType(){
	return ENT_TYPE_TURRET_SENSOR;
}

void TurretRange::collidedWith(Entity* entity, Manager<Entity>* manager){
	// Shoot only at Ships OR Asteroids
	if(entity->getEntityType() == ENT_TYPE_SHIP || entity->getEntityType() == ENT_TYPE_ASTEROID){
		turret->entitiesInRange->push_back(*entity);
	}
}

void TurretRange::update(int delta, Manager<Entity>* manager){
	b2Vec2 curLoc = body->GetPosition();

	vector<Entity>::iterator itr = turret->entitiesInRange->begin();
	for(; itr != turret->entitiesInRange->end(); ++itr){
		b2Vec2 entLoc = itr->getBody()->GetPosition();
		float distance = sqrt(pow(entLoc.x - curLoc.x, 2) + pow(entLoc.y - curLoc.y, 2));
		if(distance > turret->getRange()){
			turret->entitiesInRange->erase(itr);
		}
	}
}

TurretRange::~TurretRange(){

}


b2FixtureDef* buildTurretRangeFixtureDef(int size){
	b2FixtureDef* fixture = new b2FixtureDef();
	fixture->shape = buildTurretRangeShape(8, size);
	fixture->density = 1.0f;
	fixture->friction = 0.0f;
	return fixture;
}

b2BodyDef* buildTurretRangeBodyDef(int x, int y){
	b2BodyDef* bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	bodyDef->bullet = false; // TODO Should this be true?
	bodyDef->position.Set(x, y);
	return bodyDef;
}

b2PolygonShape* buildTurretRangeShape(int points, int size){
	b2PolygonShape* shape = new b2PolygonShape();

	b2Vec2 pointsArray[points];

	float deg = 0;
	for(int i = 0; i < points; i++){
		float x = cos(2 * M_PI * i / points);
		float y = sin(2 * M_PI * i / points);

		pointsArray[i] = b2Vec2(x * size, y * size);
		deg += 360.0f / points;
	}

	shape->Set(pointsArray, points);
	return shape;
}
