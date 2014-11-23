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


using namespace std;

class World {
	private:
		b2World* physicsWorld;
		vector<Entity> entities;

		float32 worldWidth;
		float32 worldHeight;

		b2Body* ship;
	public:
		World();
		void update(int delta);
		void draw(SDL_GLContext* context);

		void fire();
		void accelerate(int delta);
		void turn(int direction);

	private:
		void addAsteroid(int points, float32 roughSize, float32 x, float32 y);
		b2Body* addShip(float32 x, float32 y);
		b2Body* addBullet(float32 x, float32 y);
};


#endif /* WORLD_H_ */
