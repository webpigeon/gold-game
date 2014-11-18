//============================================================================
// Name        : gold-iggi.cpp
// Author      : Joseph Walton-Rivers & Piers Williams
// Version     :
// Copyright   : Copyright (c), 2014. All rights reserved.
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "view/Display.h"
#include "model/world.h"

using namespace std;

int main() {
	cout << "Hello, IGGI!" << endl; // prints Hello, IGGI!

	SDL_Init( SDL_INIT_EVERYTHING );

	//create display
	Display display;
	display.init();

	bool quit = false;
	while(!quit) {
		SDL_Event event;
		while(SDL_PollEvent(&event) != 0){
			if(event.type == SDL_QUIT){ quit = true;}
		}
	}

	display.close();


	SDL_Quit(); // Gracefully ish
	return 0;
}
