//============================================================================
// Name        : gold-iggi.cpp
// Author      : Joseph Walton-Rivers & Piers Williams
// Version     :
// Copyright   : Copyright (c), 2014. All rights reserved.
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "view/Display.h"
#include "model/Audio.h"
#include "GamePlaying.h"
#include "GameMessage.h"

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

	//create display
	Display display;
	display.addState("playing", new GamePlaying);
	display.addState("splash", new GameMessage("iggi-gold"));
	display.addState("complete", new GameMessage("Level complete"));
	display.addState("gameover-win", new GameMessage("you win"));
	display.addState("gameover-lose", new GameMessage("you lose"));

	display.init();

	display.changeState("splash");

	unsigned short fps = 0;
	Uint32 lastUpdateTime = SDL_GetTicks();

	bool quit = false;
	while(!quit) {
		SDL_Event event;
		while(SDL_PollEvent(&event) != 0){
			if(event.type == SDL_QUIT){ quit = true;}

			//Detect SDL key presses
	        if (event.type == SDL_KEYDOWN){
	        	display.onKeyDown(event.key.keysym.sym);
	        }
		}

		display.update(NULL);

		fps++;
		Uint32 currentTime = SDL_GetTicks();
		if (currentTime >= lastUpdateTime + 1000)
		{
			lastUpdateTime = currentTime;
			cout << "FPS: " << fps << endl;
			fps = 0;
		}
	}

	display.close();


	SDL_Quit(); // Gracefully ish
	return 0;
}
