/*
 * Display.h
 *
 *  Created on: 18 Nov 2014
 *      Author: webpigeon
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL2/SDL.h>
#include "../model/world.h"

class Display {

public:
	Display();
	virtual ~Display();
	void init(void);
	void update(World &world);
	void close(void);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Uint32 lastLoop;

};

#endif /* DISPLAY_H_ */

