/*
 * asteroid.cpp
 *
 *  Created on: 19 Nov 2014
 *      Author: piers
 */
#include "asteroid.h"
using namespace std;

Asteroid::Asteroid(int points, float roughSize, b2Vec2 location){

	this -> points.push_back(b2Vec2(0, 0));
	this -> points.push_back(b2Vec2(0, 1));
	this -> points.push_back(b2Vec2(1, 1));
	this -> points.push_back(b2Vec2(1, 0));

	for(int i = 0; i < this -> points.size(); i++){
		this -> points[i] *= roughSize;
		this -> points[i] += location;
	}
}

