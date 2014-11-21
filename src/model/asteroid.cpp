/*
 * asteroid.cpp
 *
 *  Created on: 19 Nov 2014
 *      Author: piers
 */
#include "asteroid.h"
using namespace std;

Asteroid::Asteroid(int points, float32 roughSize, float32 x, float32 y){

	asteroidBody = 0; // Fixes warning about non-initialised member

	b2Vec2 pointsArray [this -> points.size()];

	// TODO - once I have worked how to correctly form the Asteroid the vector won't be needed
	this -> points.push_back(b2Vec2(0, 1));
	this -> points.push_back(b2Vec2(1, 1));
	this -> points.push_back(b2Vec2(1.25, 0.5));
	this -> points.push_back(b2Vec2(1, 0));
	this -> points.push_back(b2Vec2(0, 0));

	for(uint i = 0; i < this -> points.size(); i++){
		this -> points[i] *= roughSize;
		this -> points[i].x += x;
		this -> points[i].y += y;
		pointsArray[i] = this -> points[i];
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
}


