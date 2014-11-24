/*
 * Display.cpp
 *
 *  Created on: 18 Nov 2014
 *      Author: webpigeon
 */

#include "Display.h"
#include <iostream>
#include <Box2D/Box2D.h>

Display::Display() {
	window = SDL_CreateWindow("IGGI-Gold", 50, 50, 800, 640, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == NULL) {
		//TODO handle window was not created
		std::cout << "ERROR: " << SDL_GetError() << std::endl;
	}

    context = SDL_GL_CreateContext(window);
    if (context == NULL) {
    	std::cout << "ERROR: " << SDL_GetError() << std::endl;
    }
}

void Display::init(void) {
    // Render a black background on the screen
	this->lastLoop = SDL_GetTicks();

	//Set OpenGL attributes for SDL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	//set OpenGL to vsync mode
	SDL_GL_SetSwapInterval(1);

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	//setup opengl stuff
	glMatrixMode(GL_PROJECTION);
	glOrtho( 0, 80, 64, 0, -1, 1 );
}

void Display::update(World &world, Entity *player) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glClearColor ( 0.0, 0.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );

    if (player != NULL) {
    	b2Vec2 playerPos = player->getBody()->GetWorldCenter();
    	glTranslatef(playerPos.x, playerPos.y, 0);
    }

    //Stage 1 - Game Updates
    Uint32 currTime = SDL_GetTicks();
    int delta = currTime - lastLoop;
    lastLoop = currTime;
    world.update(delta);

    //Stage 2 - rendering code
    world.draw(&context);

    SDL_GL_SwapWindow(window);
}

void Display::close(void) {
}

Display::~Display() {
	// TODO Auto-generated destructor stub

	//Deallocate renderer
	SDL_GL_DeleteContext(context);

	//Destroy window
	SDL_DestroyWindow( window );
	window = NULL;
}

