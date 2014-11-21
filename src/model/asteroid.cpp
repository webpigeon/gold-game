/*
 * asteroid.cpp
 *
 *  Created on: 19 Nov 2014
 *      Author: piers
 */
#include "asteroid.h"
#include <assert.h>
#include <iostream>

using namespace std;

Asteroid::Asteroid(int points, float32 roughSize, float32 x, float32 y){
	assert (points >= 1);

	asteroidBody = 0; // Fixes warning about non-initialised member
	pointsArray = new b2Vec2[points];
	pointsLength = points;


	// TODO - once I have worked how to correctly form the Asteroid the vector won't be needed
	this -> pointsArray[0] = (b2Vec2(0, 1));
	this -> pointsArray[1] = (b2Vec2(1, 1));
	this -> pointsArray[2] = (b2Vec2(1.25, 0.5));
	this -> pointsArray[3] = (b2Vec2(1, 0));
	this -> pointsArray[4] = (b2Vec2(0, 0));

	for(int i = 0; i < points; i++){
		this -> pointsArray[i] *= roughSize;
		this -> pointsArray[i].x += x;
		this -> pointsArray[i].y += y;
	}

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);

	asteroidShape.Set(pointsArray, points);

	asteroidFixture.shape = &asteroidShape;
	asteroidFixture.density = 1.0f; // TODO - Work out exactly what this means
	asteroidFixture.friction = 0.0f; // No friction in space
}

b2BodyDef& Asteroid::getBodyDef(){
	return bodyDef;
}

void Asteroid::insertBody(b2Body* body){
	this -> asteroidBody = body;
	this -> asteroidBody -> CreateFixture(&asteroidFixture);
	this -> asteroidBody -> ApplyLinearImpulse( b2Vec2(rand() * 10, rand() * 10), asteroidBody->GetWorldCenter(), true );
}

void Asteroid::draw(SDL_Renderer* renderer){
	int r = 0;
	int g = 255;
	int b = 0;
	int a = 255;

	Sint16 vx[pointsLength];
	Sint16 vy[pointsLength];

	b2Vec2 pos = asteroidBody->GetPosition();
	float angle = asteroidBody->GetAngle();

	for(int i = 0; i < pointsLength; i++){
		vx[i] = pointsArray[i].x + pos.x;
		vy[i] = pointsArray[i].y + pos.y;
	}

	polygonRGBA(renderer, vx, vy, pointsLength, r, g, b, a);
}


