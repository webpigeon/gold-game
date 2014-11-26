/*
 * asteroid.cpp
 *
 *  Created on: 19 Nov 2014
 *      Author: piers
 */
#include "asteroid.h"
#include <assert.h>
#include <iostream>

#include <cmath>

using namespace std;

static b2PolygonShape* buildAsteroidShape(int points, float32 size);

Asteroid::Asteroid(b2Body* body, float32 size) : Entity(body){
	body->CreateFixture(buildAsteroidFixtureDef(size));
	body->ApplyLinearImpulse(b2Vec2(body->GetMass(), body->GetMass()), body->GetWorldCenter(), true);
	body->ApplyAngularImpulse(body->GetMass() * 20, true);
	//(b2Vec2(50, 50), true);
}

void Asteroid::collidedWith(Entity* entity, Manager<Entity>* manager) {
	// when an asteroid is hit, distroy it
	manager->remove(this);
}

int Asteroid::getEntityType() {
	return ENT_TYPE_ASTEROID;
}

b2FixtureDef* buildAsteroidFixtureDef(float32 size){
	b2FixtureDef* fixture = new b2FixtureDef();
	fixture->shape = buildAsteroidShape(8, size);
	fixture->density = 1.0f;
	fixture->friction = 0.0f;
	return fixture;
}

b2BodyDef* buildAsteroidBodyDef(int x, int y){
	b2BodyDef* bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	bodyDef->position.Set(x, y);
	return bodyDef;
}

b2PolygonShape* buildAsteroidShape(int points, float32 size) {
	b2PolygonShape* shape = new b2PolygonShape();

	b2Vec2 pointsArray[points];

	for(int i = 0; i < points; i++){
		float x = cos(2 * M_PI * i / points);
		float y = sin(2 * M_PI * i / points);

		float xMod = (rand() % 20 / 100.0) - 0.1;
		float yMod = (rand() % 20 / 100.0) - 0.1;

		pointsArray[i] = b2Vec2((x + xMod) * size, (y + yMod) * size);
	}

	shape->Set(pointsArray, points);
	return shape;
}

