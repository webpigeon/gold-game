/*
 * Entity.cpp
 *
 *  Created on: 19 Nov 2014
 *      Author: piers
 */

#include "Entity.h"
#include <iostream>

#define RAD_TO_DEG_FACTOR 57.2957795

Entity::Entity(b2Body* body) {
	this->body = body;
	body->SetUserData(this);
}

Entity::~Entity() {
	body->GetWorld()->DestroyBody( body );
}

void Entity::init() {

}

b2Body* Entity::getBody() {
	return this->body;
}

void Entity::draw(){
	b2Vec2 pos = body->GetWorldCenter();
	float angle = body->GetAngle() * RAD_TO_DEG_FACTOR;

	//set shape
	glColor3f(0, 1.0f, 0);
	glPushMatrix();

	//move the origin to the asteroid
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle, 0, 0, 1);

	// now we start drawing stuff

	b2Fixture* f = body->GetFixtureList();
	while (f) {
		b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
		int vertexCount = shape->GetVertexCount();

		glBegin(GL_POLYGON);
		for (int i=0; i<vertexCount; ++i) {
			b2Vec2 vertex = shape->GetVertex(i);
			glVertex2f(vertex.x, vertex.y);
		}
		glEnd();

		f = f->GetNext();
	}

	glPopMatrix();
}

void Entity::collidedWith(Entity* entity, Manager<Entity>* manager) {
	std::cout << "Entity collide method called" << std::endl;
}

int Entity::getEntityType() {
	return ENT_TYPE_UNDEFINED;
}

