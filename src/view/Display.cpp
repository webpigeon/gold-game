/*
 * Display.cpp
 *
 *  Created on: 18 Nov 2014
 *      Author: webpigeon
 */

#include "Display.h"
#include <iostream>

Display::Display() {
	window = SDL_CreateWindow("IGGI-Gold", 50, 50, 800, 640, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		//TODO handle window was not created
	}

	screen = SDL_GetWindowSurface( window );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
    	std::cout << "ERROR: " << SDL_GetError() << std::endl;
    }
}

void Display::init(void) {
    // Render a black background on the screen
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //SDL_RenderClear(renderer);
    //SDL_RenderPresent(renderer);
}

void Display::update(World &world) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // fills screen with the colour
    //SDL_FillRect(screen, NULL,  0xFFFFFF);
    //std::cout << SDL_GetError();

    //TODO rendering code here
    world.draw(renderer);

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

