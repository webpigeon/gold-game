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

static b2PolygonShape* buildAsteroidShape(int points, int size);

Asteroid::Asteroid(b2Body* body) : Entity(body){
}

b2FixtureDef* buildAsteroidFixtureDef(int p, int size){
	b2FixtureDef* fixture = new b2FixtureDef();
	fixture->shape = buildAsteroidShape(p, size);
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

b2PolygonShape* buildAsteroidShape(int points, int size) {
	b2PolygonShape* shape = new b2PolygonShape();

	b2Vec2 pointsArray[points];

	float deg = 0;
	for(int i = 0; i < points; i++){
		float x = cos(2 * M_PI * i / points);
		float y = sin(2 * M_PI * i / points);

		float xMod = (rand() % 20 / 100.0) - 0.1;
		float yMod = (rand() % 20 / 100.0) - 0.1;

		cout << "x" << x << " xMod" << xMod << endl;

		pointsArray[i] = b2Vec2((x + xMod) * size, (y + yMod) * size);
		deg += 360.0f / points;
	}

	shape->Set(pointsArray, points);
	return shape;
}

