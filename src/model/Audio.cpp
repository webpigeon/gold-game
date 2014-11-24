/*
 * Audio.cpp
 *
 *  Created on: 24 Nov 2014
 *      Author: piers
 */

#include "Audio.h"

using namespace std;

Audio::Audio() {
	// TODO Auto-generated constructor stub
	explosion = Mix_LoadWAV("/Assets/Sounds/explode.wav");
	laser = Mix_LoadWAV("/Assets/Sounds/laser.wav");

	if(explosion == NULL){
		cout << "Couldn't find explosion" << endl;
	}
}

void Audio::playExplosion(){
	Mix_PlayChannel(-1, explosion, 0);
}

void Audio::playLaser(){
	Mix_PlayChannel(-1, laser, 0);
}

Audio::~Audio() {
	// TODO Auto-generated destructor stub

	Mix_FreeChunk(explosion);
	Mix_FreeChunk(laser);
}

