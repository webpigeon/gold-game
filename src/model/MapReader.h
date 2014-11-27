/*
 * MapReader.h
 *
 *  Created on: 24 Nov 2014
 *      Author: piers
 */

#ifndef MAPREADER_H_
#define MAPREADER_H_

#include <vector>
#include "Entity.h"
#include "World.h"
#include "Manager.h"
#include "Asteroid.h"
#include "GoalObject.h"
#include "Turret.h"
#include "Projectile.h"


using namespace std;

class MapReader {
private:
	SDL_Texture* texture;
	void* pixels;
	Uint32* pixelData;
	int pitch;
	int width;
	int height;

public:
	MapReader();
	virtual ~MapReader();

	void loadMap(const char* name, Manager<Entity>* world, b2Vec2& playerPosition);

private:
	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	int getPitch();
};

#endif /* MAPREADER_H_ */
