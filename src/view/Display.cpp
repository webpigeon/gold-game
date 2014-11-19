/*
 * Display.cpp
 *
 *  Created on: 18 Nov 2014
 *      Author: webpigeon
 */

#include "Display.h"

Display::Display() {
	window = SDL_CreateWindow("IGGI-Gold", 50, 50, 800, 640, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		//TODO handle window was not created
	}

	screen = SDL_GetWindowSurface( window );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
}

void Display::init(void) {
    // Render a black background on the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Display::update(World &world) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //TODO rendering code here
    world.draw();

    SDL_RenderPresent(renderer);
}

void Display::close(void) {
}

Display::~Display() {
	// TODO Auto-generated destructor stub

	//Deallocate renderer
    SDL_DestroyRenderer(renderer);

	//Deallocate surface
	SDL_FreeSurface( screen );
	screen = NULL;

	//Destroy window
	SDL_DestroyWindow( window );
	window = NULL;
}

