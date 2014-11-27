/*
 * MapReader.cpp
 *
 *  Created on: 24 Nov 2014
 *      Author: piers
 */

#include "MapReader.h"
#include "SDL2/SDL_image.h"

#include <iostream>

using namespace std;

MapReader::MapReader() {
	// TODO Auto-generated constructor stub

}

void MapReader::loadMap(const char* name, Manager<Entity>* world){
	cout << "Loading map: " << name << endl;
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(name);

//	cout << "Gets here" << endl;

	width = loadedSurface->w;
	height = loadedSurface->h;
//	cout << "Gets here" << endl;

	if(loadedSurface == NULL){
			cout << "Unable to load image " << name << endl;
	}else{
		// Lock texture, give it reference to pixels
		SDL_LockTexture(newTexture, NULL, &pixels, &pitch);

		pixelData = (Uint32*)loadedSurface->pixels;

		//Iterate through the pixels!!
		for(int i = 0; i < width * height; i++){
			if(pixelData[i] == 0){
				// Make wall
//				cout << "Wall: (X: " << i % width << " Y: " << (i / width) << endl;
				float32 x = (i % width) * 10;
				float32 y = (i / width) * 10;
				world->add(new Wall(x, y, 5));
			}
		}

		// build some asteroids
		for(int i=1; i<2; i++){
			float x = i * 60;
			float y = i * 60;
			world->add(new Asteroid(x, y, 10));
		}

		world->add(new GoalObject(50, 50, 10));

		// Unlock texture, it now has its own copy of pixels
		SDL_UnlockTexture(newTexture);

		// Free the pixels
		pixels = NULL;

		// Free the surface
		SDL_FreeSurface(loadedSurface);
	}
	cout << "DEBUG: world has been loaded." << endl;
}

bool MapReader::lockTexture(){
	bool success = true;

	if(pixels != NULL){
		success = false;
		cout << "Texture is already locked" << endl;
	}else{
		if(SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0){
			success = false;
			cout << "Failed to lock texture" << SDL_GetError() << endl;
		}
	}

	return success;

}

bool MapReader::unlockTexture(){
	bool success = true;
	if(pixels == NULL){
		success = false;
		cout << "Texture is already unlocked!" << endl;
	}else{
		SDL_UnlockTexture(texture);
		pixels = NULL;
		pitch = 0;
	}
	return success;
}

void* MapReader::getPixels(){
	return pixels;
}

int MapReader::getPitch(){
	return pitch;
}

MapReader::~MapReader() {
	// TODO Auto-generated destructor stub
}

