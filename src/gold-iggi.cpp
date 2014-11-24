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
#include "model/Audio.h"
#include "model/Model.h"


using namespace std;

int main() {
	cout << "Hello, IGGI!" << endl; // prints Hello, IGGI!

	int errorCode = SDL_Init( SDL_INIT_EVERYTHING );
	if (errorCode != 0) {
		cout << "ERROR: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
		cout << "ERROR: Something musical went wrong" << endl;
		return EXIT_FAILURE;
	}

	World world;
	Entity* playerShip = world.addShip(50, 50);

	Model model(&world, playerShip);
	world.addColliderCallback(&model);

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

			//Detect SDL key presses
	        if (event.type == SDL_KEYDOWN){
	        	switch(event.key.keysym.sym) {
	        		case SDLK_UP:
	        			cout << "accerlate ship!" << endl;
	        			model.accelerate(-1);
	        			break;

	        		case SDLK_DOWN:
	        			cout << "decelerate ship!" << endl;
	        			model.accelerate(1);
	        			break;

	        		case SDLK_LEFT:
	        			cout << "Turn counterclockwise!" << endl;
	        			model.turn(-1);
	        			break;

	        		case SDLK_RIGHT:
	        			cout << "Turn clockwise!" << endl;
	        			model.turn(1);
	        			break;

	        		case SDLK_SPACE:
	        			cout << "Firing" << endl;
	        			model.fire();
	        			break;
	        	}

	        }
		}

		display.update(world, playerShip);

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
