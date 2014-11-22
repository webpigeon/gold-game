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

		float x1 = cos(2 * M_PI * i / points);
		float y1 = sin(2 * M_PI * i / points);
		//float tX = x * cos(theta) - y * sin(theta);

		//y = x * sin(theta) + y * cos(theta);
		//x = tX;

		cout << "X: " << x << " Y: " << y << endl;
		this -> pointsArray[i] = (b2Vec2(x1, y1));
		deg += 360.0f / points;
	}

	for(int i = 0; i < points; i++){
		this -> pointsArray[i] *= roughSize;
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
	this -> asteroidBody -> ApplyLinearImpulse( b2Vec2(rand() * 0.1, rand() * 0.1), asteroidBody->GetWorldCenter(), true );
}

void Asteroid::draw(SDL_GLContext* renderer){
	b2Vec2 pos = asteroidBody->GetPosition();
	float angle = asteroidBody->GetAngle();

	glColor3f(0, 1.0f, 0);
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle, 0, 0, 1);
	glBegin(GL_POLYGON);

	for(int i = 0; i < pointsLength; i++){
		glVertex2f(pointsArray[i].x, pointsArray[i].y);
	}

	glEnd();

	glPopMatrix();
}


