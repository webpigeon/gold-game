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
#include <string>
#include "../model/world.h"

class Display {

public:
	Display();
	virtual ~Display();
	void init(void);
	void renderText(const TTF_Font *font, float32 x, float32 y, const std::string& Text);
	void update(World &world, Entity *center);
	void close(void);

private:
	SDL_Window* window;
	SDL_GLContext context;
	Uint32 lastLoop;
	TTF_Font* font;

};

#endif /* DISPLAY_H_ */

