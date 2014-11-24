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
	explosion = Mix_LoadWAV("Assets/Sound/explode.wav");
	laser = Mix_LoadWAV("Assets/Sound/laser.wav");

	if(explosion == NULL){
		cout << "Couldn't find explosion" << endl;
	}
	if(laser == NULL){
		cout << "Couldn't find ma laser!" << endl;
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

