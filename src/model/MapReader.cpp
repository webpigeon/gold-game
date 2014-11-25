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

void MapReader::loadMap(char* name){
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(name);

	width = loadedSurface->w;
	height = loadedSurface->h;

	if(loadedSurface == NULL){
			cout << "Unable to load image " << name << endl;
	}else{
		// Lock texture, give it reference to pixels
		SDL_LockTexture(newTexture, NULL, &pixels, &pitch);

		// Put data into pixels
		memcpy(pixels, loadedSurface->pixels, loadedSurface->pitch * loadedSurface->h);

		pixelData = (Uint32*)pixels;

		//Iterate through the pixels!!
		for(int i = 0; i < width * height; i++){
			if(pixelData[i] == 0){
				// Make wall
				cout << "Wall: (X: " << i % width << " Y: " << (i / width) + 1 << endl;
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

