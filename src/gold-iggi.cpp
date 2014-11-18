//============================================================================
// Name        : gold-iggi.cpp
// Author      : Joseph Walton-Rivers & Piers Williams
// Version     :
// Copyright   : Copyright (c), 2014. All rights reserved.
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL2/SDL.h>
#include "model/world.h"

using namespace std;

int main() {
	 //Start SDL
	SDL_Init( SDL_INIT_EVERYTHING );

	cout << "Hello, IGGI!" << endl; // prints Hello, IGGI!
	SDL_Window* screen = SDL_CreateWindow("IGGI-Gold", 50, 50, 800, 640, SDL_WINDOW_SHOWN);

	bool quit = false;
	while(!quit) {
		SDL_Event event;
		while(SDL_PollEvent(&event) != 0){
			if(event.type == SDL_QUIT){ quit = true;}
		}
	}



	SDL_Quit(); // Gracefully ish
	return 0;
}
