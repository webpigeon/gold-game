/*
 * Turret.cpp
 *
 *  Created on: 25 Nov 2014
 *      Author: piers
 */

#include "Turret.h"
#include <cmath>

static b2PolygonShape* buildTurretShape(int points, int size);

Turret::Turret(float32 x, float32 y, float32 size) : Entity(x, y, size), weapon(size) {
	// TODO Auto-generated constructor stub
	this->health = 50;
}

void Turret::init(Manager<Entity>* manager) {
	body = manager->buildBody(buildTurretBodyDef(initPos.x, initPos.y));
	body->SetUserData(this);
	body->CreateFixture(buildTurretFixtureDef(size));
	manager->add(this);
}

int Turret::getEntityType(){
	return ENT_TYPE_TURRET;
}

float Turret::getRange(){
	return weapon.getRange();
}

void Turret::update(int delta, Manager<Entity>* manager){
	color[0] = weapon.getHeat() / 100.0f;
	weapon.update(delta, manager, this->body);
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

TurretMiniGun::TurretMiniGun(float32 x, float32 y, float32 size) : Turret(x, y, size){
	weapon.setShotDelay(100);
	weapon.setDamagePerProjectile(5);
	weapon.setSizeOfProjectile(0.1);
	weapon.setHeatFromFiring(15);
	weapon.setMaxHeat(150);
	weapon.setMinHeat(5);
	weapon.setCoolPerSecond(145 / 2);
}
