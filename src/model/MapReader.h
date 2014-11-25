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
#include "world.h"

using namespace std;

class MapReader {
private:
	SDL_Texture* texture;
	void* pixels;
	Uint32* pixelData;
	int pitch;
	int width;
	int height;
	World* world;

public:
	MapReader(World* world);
	virtual ~MapReader();

	void loadMap(char* name);

private:
	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	int getPitch();
};

#endif /* MAPREADER_H_ */
