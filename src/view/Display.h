/*
 * Display.h
 *
 *  Created on: 18 Nov 2014
 *      Author: webpigeon
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include "../GameState.h"

class Display {

public:
	Display();
	virtual ~Display();
	void init(void);
	void update(GameState* state);
	void close(void);

private:
	SDL_Window* window;
	SDL_GLContext context;
	Uint32 lastLoop;

};

#endif /* DISPLAY_H_ */

