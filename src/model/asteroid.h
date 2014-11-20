/*
 * asteroid.h
 *
 *  Created on: 18 Nov 2014
 *      Author: piers
 */

#ifndef ASTEROID_H_
#define ASTEROID_H_
#include "Entity.h"
#include <Box2D/Box2D.h>
#include <vector>
using namespace std;


class Asteroid : public Entity {
public:
	vector<b2Vec2> points;
private:
	b2Body* asteroidBody;
	b2BodyDef bodyDef;
	b2PolygonShape asteroidBoundary;

public:

	Asteroid(int points, float32 roughSize, float32 x, float32 y);
	b2BodyDef& getBodyDef(void);
	void insertBody(b2Body* body);
};



#endif /* ASTEROID_H_ */
