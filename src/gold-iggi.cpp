//============================================================================
// Name        : gold-iggi.cpp
// Author      : Joseph Walton-Rivers & Piers Williams
// Version     :
// Copyright   : Copyright (c), 2014. All rights reserved.
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL/SDL.h>
using namespace std;

int main() {
	 //Start SDL
	SDL_Init( SDL_INIT_EVERYTHING );

	cout << "Hello, IGGI!" << endl; // prints Hello, IGGI!
	SDL_Surface* screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

	bool quit = false;

	//Pause
	SDL_Event e;
	while(!quit) {
		 //Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) {
			//User requests quit
			if( e.type == SDL_QUIT ) {
				quit = true;
			}
		}
	}

	//Quit SDL
	SDL_Quit();

	return 0;
}
