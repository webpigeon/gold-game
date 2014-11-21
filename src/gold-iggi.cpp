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

	int errorCode = SDL_Init( SDL_INIT_EVERYTHING );
	if (errorCode != 0) {
		cout << "ERROR: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	World world;

	//create display
	Display display;
	display.init();

	int deltaSum = 0;
	unsigned short fps = 0;
	Uint32 lastUpdateTime = SDL_GetTicks();
	Uint32 lastLoopTime = lastUpdateTime;

	bool quit = false;
	while(!quit) {
		SDL_Event event;
		while(SDL_PollEvent(&event) != 0){
			if(event.type == SDL_QUIT){ quit = true;}
		}

		display.update(world);

		//DEBUG - keep track of the deltas for finding delta drift
	    Uint32 currTime = SDL_GetTicks();
	    deltaSum += currTime - lastLoopTime;
	    lastLoopTime = currTime;

		fps++;
		Uint32 currentTime = SDL_GetTicks();
		if (currentTime >= lastUpdateTime + 1000)
		{
			cout << fps <<  " deltaSum: " << deltaSum << endl;
			lastUpdateTime = currentTime;
			deltaSum = 0;
			fps = 0;
		}
	}

	display.close();


	SDL_Quit(); // Gracefully ish
	return 0;
}
