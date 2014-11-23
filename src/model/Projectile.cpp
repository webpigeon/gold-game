/*
 * Projectile.cpp
 *
 *  Created on: 23 Nov 2014
 *      Author: piers
 */

#include "Projectile.h"

static b2PolygonShape* buildProjectileShape(int points, int size);

Projectile::Projectile(b2Body* body) : Entity(body) {
	// TODO Auto-generated constructor stub

}

Projectile::~Projectile() {
	// TODO Auto-generated destructor stub
}

b2FixtureDef* buildProjectileFixtureDef(int size){
	b2FixtureDef* fixture = new b2FixtureDef();
	fixture->shape = buildProjectileShape(8, size);
	fixture->density = 1.0f;
	fixture->friction = 0.0f;
	return fixture;
}

b2BodyDef* buildProjectileBodyDef(int x, int y){
	b2BodyDef* bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	bodyDef->bullet = true;
	bodyDef->position.Set(x, y);
	return bodyDef;
}

b2PolygonShape* buildProjectileShape(int points, int size){
	b2PolygonShape* shape = new b2PolygonShape();

		b2Vec2 pointsArray[points];

		float deg = 0;
		for(int i = 0; i < points; i++){
			float x = cos(2 * M_PI * i / points);
			float y = sin(2 * M_PI * i / points);

			pointsArray[i] = b2Vec2(x * size, y * size);
			deg += 360.0f / points;
		}

		shape->Set(pointsArray, points);
		return shape;
}
