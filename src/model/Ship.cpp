/*
 * Ship.cpp
 *
 *  Created on: 23 Nov 2014
 *      Author: piers
 */

#include "Ship.h"

static b2PolygonShape* buildShipShape();

Ship::Ship(float32 x, float32 y, float32 size) : Entity(x, y, size){
	// TODO Auto-generated constructor stub
}

void Ship::init(Manager<Entity>* manager) {
	body = manager->buildBody(buildShipBodyDef(initPos.x, initPos.y));
	body->SetUserData(this);

	//create ship body
	b2FixtureDef fixture;
	fixture.shape = buildShipShape();
	fixture.density = 1.0f;
	fixture.friction = 0.0f;
	this->body->CreateFixture(&fixture);

	//create ship left engine
	b2PolygonShape shape;
	//shape.SetAsBox(1, 1);
	b2Vec2 points[4];
	points[0] = b2Vec2(-0.5 * 2, 0.75 * 2);
	points[1] = b2Vec2(-0.5 * 2, 0 * 2);
	points[2] = b2Vec2(-0.75 * 2, 0 * 2);
	points[3] = b2Vec2(-0.75 * 2, 0.75 * 2);
	shape.Set(points, 4);
	fixture.shape = &shape;
	this->body->CreateFixture(&fixture);

	//shape.SetAsBox(1, 1);
	points[0] = b2Vec2(0.5 * 2, 0.75 * 2);
	points[1] = b2Vec2(0.5 * 2, 0 * 2);
	points[2] = b2Vec2(0.75 * 2, 0 * 2);
	points[3] = b2Vec2(0.75 * 2, 0.75 * 2);
	shape.Set(points, 4);
	fixture.shape = &shape;
	this->body->CreateFixture(&fixture);
}

void Ship::collidedWith(Entity* entity, Manager<Entity>* manager){
	manager->remove(this);
}

b2Body* Ship::getBody(){
	return this->body;
}

int Ship::getEntityType() {
	return ENT_TYPE_SHIP;
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
	bodyDef->linearDamping = 1.0f;
	bodyDef->angularDamping = 1.0f;
	return bodyDef;
}

b2PolygonShape* buildShipShape(){
	b2PolygonShape* shape = new b2PolygonShape();
	b2Vec2 pointsArray[4];

	float size = 2;	glEnd();

	pointsArray[0] = b2Vec2(-0.5 * size, 1 * size);
	pointsArray[1] = b2Vec2(-0.5 * size, -1 * size);
	pointsArray[2] = b2Vec2(0.5 * size, -1 * size);
	pointsArray[3] = b2Vec2(0.5 * size, 1 * size);

	shape -> Set(pointsArray, 4);
	return shape;

}


