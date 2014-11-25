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
#include "model/MapReader.h"


using namespace std;

int main() {
	cout << "Hello, IGGI!" << endl; // prints Hello, IGGI!

	int errorCode = SDL_Init( SDL_INIT_EVERYTHING );
	if (errorCode != 0) {
		cerr << "ERROR: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
		cerr << "ERROR: Something musical went wrong" << endl;
		return EXIT_FAILURE;
	}

	World world;
	Entity* playerShip = world.addShip(20, 20);

	for(int i = 1; i < 5; i++){
		int x = rand() % 80;
		int y = rand() % 60;

		world.addAsteroid(8, 4, x, y);
	}

	Model model(&world, playerShip);
	world.addColliderCallback(&model);

	MapReader reader(&world);
	reader.loadMap("Assets/Maps/map1.bmp");

	//create display
	Display display;
	display.init();

	unsigned short fps = 0;
	Uint32 lastUpdateTime = SDL_GetTicks();

	bool quit = false;
	while(!quit) {
		SDL_Event event;
		while(SDL_PollEvent(&event) != 0){
			if(event.type == SDL_QUIT){ quit = true;}

			//Detect SDL key presses
	        if (event.type == SDL_KEYDOWN){
	        	switch(event.key.keysym.sym) {
	        		case SDLK_UP:
	        			model.accelerate(-1);
	        			break;

	        		case SDLK_DOWN:
	        			model.accelerate(1);
	        			break;

	        		case SDLK_LEFT:
	        			model.turn(-1);
	        			break;

	        		case SDLK_RIGHT:
	        			model.turn(1);
	        			break;

	        		case SDLK_SPACE:
	        			model.fire();
	        			break;
	        	}

	        }
		}

		display.update(world, model.getPlayer());

		fps++;
		Uint32 currentTime = SDL_GetTicks();
		if (currentTime >= lastUpdateTime + 1000)
		{
			lastUpdateTime = currentTime;
			fps = 0;
		}
	}

	display.close();


	SDL_Quit(); // Gracefully ish
	return 0;
}
