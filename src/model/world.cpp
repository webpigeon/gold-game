/*
 * world.cpp

 *
 *  Created on: 18 Nov 2014
 *      Author: piers
 */

#include "world.h"
#include <iostream>

#define VEL_INTER 8
#define POS_INTER 3
#define DELTA_PER_SEC 1000.0
#define WEAPON_COOLDOWN 500

World::World(){
	weaponCooldown = 0;
	b2Vec2 gravity(0.0f, 0.0f);
	physicsWorld = new b2World(gravity);

	for(int i = 1; i < 5; i++){
		int x = rand() % 80;
		int y = rand() % 60;

		cout << "SPAWN: " << x << "," << y << endl;

		addAsteroid(8, 4, x, y);
	}

	addWall(5, 20, 20);

	ship2 = addShip(50, 50);

}

void World::addColliderCallback(b2ContactListener* callback) {
	physicsWorld->SetContactListener(callback);
}

void World::update(int delta) {
	//std::cout << "delta: " << delta / DELTA_PER_SEC << std::endl;
	physicsWorld->Step(delta/DELTA_PER_SEC, VEL_INTER, POS_INTER);

	//kill all dead entities
	std::vector<Entity*>::iterator it = killList.begin();
	std::vector<Entity*>::iterator end = killList.end();
	for (; it!=end; ++it) {
		Entity* entity = *it;

		delete entity;
		std::vector<Entity*>::iterator it = std::find(entities.begin(), entities.end(), entity);
		if (it != entities.end()) {
			entities.erase(it);
		}
	}

	killList.clear();
}

void World::draw(SDL_GLContext* context){

	b2Vec2 shipPos = ship2->GetWorldCenter();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-shipPos.x + 40, -shipPos.y + 30, 0);

	std::vector<Entity*>::iterator it = entities.begin();
	std::vector<Entity*>::iterator end = entities.end();
	for (; it!=end; ++it) {
		Entity* entity = *it;
		entity->draw(context);
	}
}

void World::addAsteroid(int points, float32 roughSize, float32 x, float32 y){
	//create the required components
	b2FixtureDef* fixture = buildAsteroidFixtureDef(points, roughSize);
	b2BodyDef* bodyDef = buildAsteroidBodyDef(x, y);

	//create the asteroid and add it
	b2Body* body = physicsWorld->CreateBody(bodyDef);
	body->CreateFixture(fixture);
	Asteroid* temp = new Asteroid(body);
	this->entities.push_back(temp);

	//TODO find out if it's safe to delete fixture and bodydef here
}

void World::remove(Entity* entity) {
	killList.push_back(entity);
}

void World::accelerate(int delta) {
	b2Vec2 speed(0, delta * 150);
	b2Vec2 force = ship2->GetWorldVector(speed);
	ship2->ApplyForce(force, ship2->GetWorldCenter(), true);
}

void World::turn(int direction) {
	float w = ship2->GetAngularVelocity();
	w += direction;

	if (w > 2) w = 2;
	if (w < -2) w = -2;

	ship2->SetAngularVelocity(w);
}

b2Body* World::addShip(float32 x, float32 y){
	b2FixtureDef* fixture = buildShipFixtureDef();
	b2BodyDef* bodyDef = buildShipBodyDef(x, y);
	b2Body* body = physicsWorld -> CreateBody(bodyDef);
	body -> CreateFixture(fixture);
	Ship* temp = new Ship(body);
	ship = temp;
	this ->entities.push_back(temp);

	return body;
}

b2Body* World::addBullet(float32 x, float32 y, float32 angle) {
	b2FixtureDef* fixture = buildShipFixtureDef();
	b2BodyDef* bodyDef = buildShipBodyDef(x, y);
	bodyDef->bullet = true;
	bodyDef->angle = angle;

	b2Body* body = physicsWorld->CreateBody(bodyDef);

	body->CreateFixture(fixture);
	Entity* tmp = new Entity(body);
	this->entities.push_back(tmp);

	return body;
}

void World::addProjectile(float32 size, float32 x, float32 y, b2Vec2 initialVelocity){
	b2FixtureDef* fixture = buildProjectileFixtureDef(size);
	b2BodyDef* bodyDef = buildProjectileBodyDef(x, y);
	b2Body* body = physicsWorld -> CreateBody(bodyDef);
	body -> CreateFixture(fixture);
	Projectile* temp = new Projectile(body, initialVelocity);
	this -> entities.push_back(temp);
}

void World::fire(){
	uint32 currentTime = SDL_GetTicks();
	int delta = currentTime-weaponCooldown;
	if(delta > WEAPON_COOLDOWN){
		b2Vec2 loc = ship2->GetPosition();
		b2Vec2 offset = ship2->GetWorldVector(b2Vec2(0, -1));
		addProjectile(1, loc.x + (offset.x * 5), loc.y + (offset.y * 5), b2Vec2(offset.x * 500, offset.y * 500));
		weaponCooldown = currentTime;
	}
}

void World::addWall(float32 size, float32 x, float32 y){
	b2FixtureDef* fixture = buildWallFixtureDef(size);
	b2BodyDef* bodyDef = buildWallBodyDef(x, y);
	b2Body* body = physicsWorld -> CreateBody(bodyDef);
	body -> CreateFixture(fixture);
	Wall* temp = new Wall(body);
	this   -> entities.push_back(temp);
}



