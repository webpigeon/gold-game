/*
 * asteroid.cpp
 *
 *  Created on: 19 Nov 2014
 *      Author: piers
 */
#include "asteroid.h"
using namespace std;

Asteroid::Asteroid(int points, float32 roughSize, float32 x, float32 y){

	this -> points.push_back(b2Vec2(0, 0));
	this -> points.push_back(b2Vec2(0, 1));
	this -> points.push_back(b2Vec2(1, 1));
	this -> points.push_back(b2Vec2(1, 0));

	for(int i = 0; i < this -> points.size(); i++){
		this -> points[i] *= roughSize;
		this -> points[i].x += x;
		this -> points[i].y += y;
	}

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
}

b2BodyDef& Asteroid::getBodyDef(){
	return bodyDef;
}

void Asteroid::insertBody(b2Body* body){
	this -> asteroidBody = body;
}


