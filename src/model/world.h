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
#include "asteroid.h"
#include "Ship.h"
#include <vector>
#include "Projectile.h"
#include "Wall.h"
#include "Manager.h"

class World : public Manager<Entity> {
	private:
		b2World* physicsWorld;
		std::vector<Entity*> entities;
		std::vector<Entity*> killList;

		float32 worldWidth;
		float32 worldHeight;

	public:
		World();
		void update(int delta);
		void draw(SDL_GLContext* context);
		void add(Entity* entity);
		void remove(Entity* entity);
		void addColliderCallback(b2ContactListener* callback);
		void addAsteroid(int points, float32 roughSize, float32 x, float32 y);
		void addProjectile(float32 size, float32 x, float32 y, b2Vec2 initialVelocity);
		void addWall(float32 size, float32 x, float32 y);
		Entity* addShip(float32 x, float32 y);
		Entity* addBullet(float32 x, float32 y, float32 angle);
};


#endif /* WORLD_H_ */
