/*
 * Wall.cpp
 *
 *  Created on: 24 Nov 2014
 *      Author: piers
 */

#include "Wall.h"

static b2PolygonShape* buildWallShape(float32 size);

Wall::Wall(float32 x, float32 y, float32 size, bool distructable) : Entity(x, y, size){
	// TODO Auto-generated constructor stub
	this->distructable = distructable;
	this->health = 1000;
}

void Wall::init(Manager<Entity>* manager) {
	body = manager->buildBody(buildWallBodyDef(initPos.x, initPos.y));
	body->SetUserData(this);
	body->CreateFixture(buildWallFixtureDef(size));
	health = 51;
}

int Wall::getEntityType(){
	return ENT_TYPE_WALL;
}

void Wall::collidedWith(Entity* entity, Manager<Entity>* manager){
	// Specifically must do nothing with collision
	if (distructable && entity->getEntityType() == ENT_TYPE_BULLET) {
		health -= entity->getHealth();
		if (health <= 0) {
			manager->remove(this);
		}
	}

}

Wall::~Wall() {
	// TODO Auto-generated destructor stub
}

b2FixtureDef* buildWallFixtureDef(float32 size){
	b2FixtureDef* fixture = new b2FixtureDef();
	fixture -> shape = buildWallShape(size);
	fixture -> density = 1.0f;
	fixture -> friction = 0.0f;
	return fixture;
}
b2BodyDef* buildWallBodyDef(float32 x, float32 y){
	b2BodyDef* bodyDef = new b2BodyDef();
	bodyDef -> type = b2_staticBody;
	bodyDef -> position.Set(x, y);
	return bodyDef;
}
b2PolygonShape* buildWallShape(float32 size){
	b2PolygonShape* shape = new b2PolygonShape();
	shape->SetAsBox(size, size);
	return shape;
}

