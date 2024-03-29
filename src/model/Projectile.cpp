/*
 * Projectile.cpp
 *
 *  Created on: 23 Nov 2014
 *      Author: piers
 */

#include "Projectile.h"
#include <iostream>

static b2CircleShape* buildProjectileShape(int points, float32 size);



Projectile::Projectile(float32 x, float32 y, b2Vec2 initialVelocity, float32 size, float32 damage) :  Entity(x, y, size), initVelocity(initialVelocity) {
	// TODO Auto-generated constructor stub
	health = 100;
	this->damage = damage;
	generatePoints();
}

void Projectile::init(Manager<Entity>* manager) {
	//build the projectile
	body = manager->buildBody(buildProjectileBodyDef(initPos.x, initPos.y));
	body->CreateFixture(buildProjectileFixtureDef(size));
	body->SetUserData(this);
	manager->add(this);

	body->ApplyLinearImpulse(initVelocity, body->GetWorldCenter(), true);
}

float32 Projectile::getHealth(){
	return damage * (health / 100.0f);
}

Projectile::~Projectile() {
	// TODO Auto-generated destructor stub
	delete[] pointsArray;
}

void Projectile::collidedWith(Entity* entity, Manager<Entity>* manager) {
	manager->remove(this);
}

int Projectile::getEntityType() {
	return ENT_TYPE_BULLET;
}

void Projectile::update(int delta, Manager<Entity>* manager){
	health -= (delta * 0.25);
	if (health <= 0) {
		manager->remove(this);
	}
}

void Projectile::draw(){
	b2Vec2 pos = body->GetWorldCenter();

	glColor3f(1.0f, 0, 0);
	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0);

	b2Fixture* fixtures = body->GetFixtureList();

	glBegin(GL_POLYGON);
	while(fixtures){
		b2CircleShape* shape = (b2CircleShape*)fixtures->GetShape();
		float radius = shape->m_radius;
		b2Vec2 offset = shape->m_p;

		for(int i = 0; i < pointsLength; i++){
			glVertex2f((pointsArray[i].x) * radius, (pointsArray[i].y) * radius);
		}

		fixtures = fixtures->GetNext();
	}

	glEnd();
	glPopMatrix();

}

void Projectile::generatePoints(){
	pointsLength = 32;
	pointsArray = new b2Vec2[pointsLength];
	for(int i = 0; i < pointsLength; i++){
		float x = cos(2 * M_PI * i / pointsLength);
		float y = sin(2 * M_PI * i / pointsLength);
		pointsArray[i] = b2Vec2(x, y);
	}
}

b2FixtureDef* buildProjectileFixtureDef(float32 size){
	b2FixtureDef* fixture = new b2FixtureDef();
	fixture->shape = buildProjectileShape(8, size);
	fixture->density = 0.7f;
	fixture->friction = 0.0f;
	return fixture;
}

b2BodyDef* buildProjectileBodyDef(float32 x, float32 y){
	b2BodyDef* bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	bodyDef->bullet = true;
	bodyDef->position.Set(x, y);
	return bodyDef;
}


b2CircleShape* buildProjectileShape(int points, float32 size){
	b2CircleShape* shape = new b2CircleShape();
	shape->m_p.Set(0, 0);
	shape->m_radius = size;
	return shape;
}
