/*
 * Ship.cpp
 *
 *  Created on: 23 Nov 2014
 *      Author: piers
 */

#include "Ship.h"

static b2PolygonShape* buildShipShape();

Ship::Ship(b2Body* body) : Entity(body){
	// TODO Auto-generated constructor stub
	//body->ApplyAngularImpulse(body->GetMass() * 1000, true);
}

b2Body* Ship::getBody(){
	return this->body;
}


b2FixtureDef* buildShipFixtureDef(){
	b2FixtureDef* fixture = new b2FixtureDef();
	fixture -> shape = buildShipShape();
	fixture -> density = 1.0f;
	fixture -> friction = 0.0f;
	return fixture;
}

b2BodyDef* buildShipBodyDef(int x, int y){
	b2BodyDef* bodyDef = new b2BodyDef();
	bodyDef -> type = b2_dynamicBody;
	bodyDef -> position.Set(x, y);
	return bodyDef;
}

b2PolygonShape* buildShipShape(){
	b2PolygonShape* shape = new b2PolygonShape();
	b2Vec2 pointsArray[3];

	float size = 20;

	pointsArray[0] = b2Vec2(0 * size, -1 * size);
	pointsArray[1] = b2Vec2(-0.5 * size, 1 * size);
	pointsArray[2] = b2Vec2(0.5 * size, 1 * size);

	shape -> Set(pointsArray, 3);
	return shape;

}


