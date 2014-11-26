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

	void loadMap(char* name, Manager<Entity>* world);

private:
	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	int getPitch();
};

#endif /* MAPREADER_H_ */
