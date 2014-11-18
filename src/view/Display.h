/*
 * Display.h
 *
 *  Created on: 18 Nov 2014
 *      Author: webpigeon
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL2/SDL.h>

class Display {

public:
	Display();
	virtual ~Display();
	void init();
	void update();
	void close();

private:
	SDL_Window* window;
	SDL_Surface* screen;
	SDL_Renderer* renderer;

};

#endif /* DISPLAY_H_ */

