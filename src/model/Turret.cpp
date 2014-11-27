/*
 * Turret.cpp
 *
 *  Created on: 25 Nov 2014
 *      Author: piers
 */

#include "Turret.h"
#include <cmath>

static b2PolygonShape* buildTurretShape(int points, int size);
static b2PolygonShape* buildTurretRangeShape(int points, int size);

Turret::Turret(float32 x, float32 y, float32 size) : Entity(x, y, size) {
	// TODO Auto-generated constructor stub
	range = 35;
	heat = 0;
	coolPerSecond = 10;
	heatFromFiring = 25;
	maxHeat = 110;
	minHeat = 35;
	cooling = false;
	canFire = true;
	tooHot = false;
	delayed = false;
	shotDelay = 500;
	msTillWeCanShoot = 0;
}

void Turret::init(Manager<Entity>* manager) {
	body = manager->buildBody(buildTurretBodyDef(initPos.x, initPos.y));
	body->SetUserData(this);
	body->CreateFixture(buildTurretFixtureDef(1));
	manager->add(this);
}

int Turret::getEntityType(){
	return ENT_TYPE_TURRET;
}

float Turret::getRange(){
	return range;
}

void Turret::update(int delta, Manager<Entity>* manager){
	calcCooldown(delta);
	calcShotDelay(delta);
//	cout << "Updating turret" << endl;

	// Can fire if we are not delayed and not tooHot
	canFire = !(delayed || tooHot);
	if(canFire){
		// Fire at something if its in range

		b2Vec2 location = body->GetWorldCenter();
		vector<Entity*>* inRange = manager->inRange(location, range);

		if(inRange->size() >= 1){
			float minDistance = range + 1;
			Entity* minEntity = NULL;
			for(vector<Entity*>::iterator  itr = inRange->begin(); itr != inRange->end(); ++itr){
				if((*itr)->getEntityType() != ENT_TYPE_WALL){
					b2Vec2 entLoc = (*itr)->getBody()->GetWorldCenter();
					float32 distance = sqrt(pow(entLoc.x - location.x, 2) + pow(entLoc.y - location.y, 2));
					if(distance < minDistance){
						minDistance = distance;
						minEntity = (*itr);
					}
				}
			}
			if(minEntity != NULL){
				b2Vec2 loc = body->GetWorldCenter();
				b2Vec2 offset = body->GetWorldVector(b2Vec2(0, -1));

				b2Vec2 target = (minEntity->getBody()->GetWorldCenter()) - loc;
				float32 desiredAngle = atan2f(target.x, -target.y);
				body->SetTransform(body->GetWorldCenter(), desiredAngle);

				b2Vec2 position(loc.x + (offset.x * 10), loc.y + (offset.y * 10));
				b2Vec2 speed(offset.x * 500, offset.y * 500);
				Projectile* proj = new Projectile(position.x, position.y,speed, 1);
				manager->add(proj);
				heat+=heatFromFiring;
			}
		}
	}
}


void Turret::collidedWith(Entity* entity, Manager<Entity>* manager){
	cout << "Turret collided with: " << entity->getEntityType() << endl;
}

void Turret::calcCooldown(int delta){
	if(cooling){
		heat -= (coolPerSecond * delta) / 1000.0f;
		if(heat <= 0){
			heat = 0;
		}
		if(heat <= 35){
			tooHot = false;
		}
	}

	if(heat > 0){
		cooling = true;
	}

	// Regardless of cooling state , must not fire after this point
	if(heat >= maxHeat){
		tooHot = true;
	}
}

void Turret::calcShotDelay(int delta){
	if(delayed){
		msTillWeCanShoot -= delta;

		if(msTillWeCanShoot <= 0){
			msTillWeCanShoot = 0;
			delayed = false;
		}
	}
}

Turret::~Turret() {
	// TODO Auto-generated destructor stub
}

b2FixtureDef* buildTurretFixtureDef(int size){
	b2FixtureDef* fixture = new b2FixtureDef();
	fixture->shape = buildTurretShape(8, size);
	fixture->density = 1.0f;
	fixture->friction = 0.0f;
	return fixture;
}

b2BodyDef* buildTurretBodyDef(int x, int y){
	b2BodyDef* bodyDef = new b2BodyDef();
	bodyDef->type=b2_staticBody;
	bodyDef->bullet = false; //TODO do we need to set this
	bodyDef->position.Set(x, y);
	return bodyDef;
}

b2PolygonShape* buildTurretShape(int points, int size){
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
