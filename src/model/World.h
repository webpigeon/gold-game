/*
 * world.h
 *
 *  Created on: 18 Nov 2014
 *      Author: piers
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include "Asteroid.h"
#include "Ship.h"
#include <vector>
#include <set>
#include <cmath>
#include "Projectile.h"
#include "Wall.h"
#include "Manager.h"
#include "Turret.h"

class World : public Manager<Entity> {
	private:
		b2World* physicsWorld;
		std::vector<Entity*> entities;
		std::set<Entity*> addList;
		std::set<Entity*> killList;

		float32 worldWidth;
		float32 worldHeight;

	public:
		World();
		void update(int delta);
		void draw();
		void add(Entity* entity);
		vector<Entity*>* inRange(b2Vec2 location, float32 range);
		b2Body* buildBody(b2BodyDef* bodyDef);
		void remove(Entity* entity);
		void addColliderCallback(b2ContactListener* callback);
		Entity* addShip(float32 x, float32 y);
};


#endif /* WORLD_H_ */
