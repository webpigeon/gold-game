/*
 * Audio.h
 *
 *  Created on: 24 Nov 2014
 *      Author: piers
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include "SDL2/SDL_mixer.h"
#include <iostream>

class Audio {
public:
	Audio();
	virtual ~Audio();
	void playExplosion();
	void playLaser();

private:
	Mix_Chunk* explosion = NULL;
	Mix_Chunk* laser = NULL;

};

#endif /* AUDIO_H_ */
