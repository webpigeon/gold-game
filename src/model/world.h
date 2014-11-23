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


using namespace std;

class World {
	private:
		b2World* physicsWorld;
		vector<Entity> entities;

		float32 worldWidth;
		float32 worldHeight;
	public:
		World();
		void update(int delta);
		void draw(SDL_GLContext* context);

		void accelerate(int delta);
		void turn(int direction);

	private:
		void addAsteroid(int points, float32 roughSize, float32 x, float32 y);
		void addShip(float32 x, float32 y);
		void addProjectile(float32 size, float32 x, float32 y, b2Vec2 initialVelocity);
};


#endif /* WORLD_H_ */
