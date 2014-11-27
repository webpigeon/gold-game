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

void MapReader::loadMap(const char* name, Manager<Entity>* world, b2Vec2& playerPosition){
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(name);

	playerPosition.x = 11;
	playerPosition.y = 11;

//	cout << "Gets here" << endl;

	width = loadedSurface->w;
	height = loadedSurface->h;
//	cout << "Gets here" << endl;

	if(loadedSurface == NULL){
			std::cerr << "Unable to load image " << name << std::endl;
	}else{
		// Lock texture, give it reference to pixels
		SDL_LockTexture(newTexture, NULL, &pixels, &pitch);

		pixelData = (Uint32*)loadedSurface->pixels;

		//Iterate through the pixels!!
		for(int i = 0; i < width * height; i++){
			uint r = (pixelData[i] >> 24) & 255;
			uint g = (pixelData[i] >> 16) & 255;
			uint b = (pixelData[i] >> 8) & 255;

			float32 x = (i % width) * 10;
			float32 y = (i / width) * 10;
			if(pixelData[i] == 0){
				world->add(new Wall(x, y, 5));
			}else if(r == 0 && g == 255 && b == 0){
				// Build asteroid
				world->add(new Asteroid(x, y, 4));
			}else if(r == 255 && g == 0 && b == 0){
				world->add(new Turret(x, y, 2));
			}else if(r == 0 && g == 255 && b == 255){
				playerPosition.Set(x, y);
			}else if(r == 255 && g == 255 && b == 0){
				world->add(new GoalObject(x, y, 1));
				cout << "Building Goal State" << endl;
			}
		}

		// Unlock texture, it now has its own copy of pixels
		SDL_UnlockTexture(newTexture);
		// Free the pixels
		pixels = NULL;

		// Free the surface
		SDL_FreeSurface(loadedSurface);
	}
}

bool MapReader::lockTexture(){
	bool success = true;

	if(pixels != NULL){
		success = false;
		std::cerr << "Texture is already locked" << std::endl;
	}else{
		if(SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0){
			success = false;
			std::cerr << "Failed to lock texture" << SDL_GetError() << std::endl;
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

