/*
 * Display.h
 *
 *  Created on: 18 Nov 2014
 *      Author: webpigeon
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>
#include <Box2D/Box2D.h>

#include <string>
#include <iostream>

#include "DisplayUtils.h"
#include "../GameState.h"


class Display : public DisplayUtils {

public:
	Display();
	virtual ~Display();
	void init(void);
	void update(GameState* state);
	void renderText(float32 x, float32 y, const std::string& Text);
	void close(void);

private:
	SDL_Window* window;
	SDL_GLContext context;
	Uint32 lastLoop;
	TTF_Font* font;

};

#endif /* DISPLAY_H_ */

