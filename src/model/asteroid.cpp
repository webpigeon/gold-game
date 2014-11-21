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

Asteroid::Asteroid(int points, float32 roughSize, float32 x, float32 y){
	assert (points >= 1);

	asteroidBody = 0; // Fixes warning about non-initialised member
	pointsArray = new b2Vec2[points];
	pointsLength = points;


	// TODO - once I have worked how to correctly form the Asteroid the vector won't be needed

	float deg = 0;
	for(int i = 0; i < points; i++){
		float theta = (180 * deg) / (M_PI );

		float x = cos(2 * M_PI * i / points);
		float y = sin(2 * M_PI * i / points);
		//float tX = x * cos(theta) - y * sin(theta);

		//y = x * sin(theta) + y * cos(theta);
		//x = tX;

		cout << "X: " << x << " Y: " << y << endl;
		this -> pointsArray[i] = (b2Vec2(x, y));
		deg += 360.0f / points;
	}



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
}

void Asteroid::draw(SDL_Renderer* renderer){
	int r = 0;
	int g = 255;
	int b = 0;
	int a = 255;

	Sint16 vx[pointsLength];
	Sint16 vy[pointsLength];

	for(int i = 0; i < pointsLength; i++){
		vx[i] = pointsArray[i].x;
		vy[i] = pointsArray[i].y;
	}

	polygonRGBA(renderer, vx, vy, pointsLength, r, g, b, a);
}


