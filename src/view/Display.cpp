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
	// Init font library
	if(!TTF_WasInit() && TTF_Init()==-1) {
		std::cerr << "TTF error: " << TTF_GetError() << std::endl;
	    exit(1);
	}

    // Render a black background on the screen
	this->lastLoop = SDL_GetTicks();
	font = TTF_OpenFont("Assets/Fonts/FreeSerif.ttf",20);
	if(!font) {
	    std::cerr << "TTF_OpenFont: " << TTF_GetError() << std::endl;
	}

	//Set OpenGL attributes for SDL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Enable openGL textures and blending
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//set OpenGL to vsync mode
	SDL_GL_SetSwapInterval(1);


	//Make things play nicely with Box2D
	glPolygonMode( GL_FRONT, GL_LINE );
	glFrontFace( GL_CW );

	//setup opengl stuff
	glMatrixMode(GL_PROJECTION);
	glOrtho( 0, 80, 64, 0, -1, 1 );
}

void Display::update(World &world, Entity *player) {
	// let the game render in world space
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 0, 80, 64, 0, -1, 1 );
	glPolygonMode( GL_FRONT, GL_LINE );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

    glClearColor ( 0.0, 0.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );

    if (player != NULL) {
    	b2Vec2 playerPos = player->getBody()->GetWorldCenter();
    	glTranslatef(-playerPos.x + 40, -playerPos.y + 30, 0);
    }

    //Stage 1 - Game Updates
    Uint32 currTime = SDL_GetTicks();
    int delta = currTime - lastLoop;
    lastLoop = currTime;
    world.update(delta);

    //Stage 2 - rendering code
    world.draw(&context);

    glPopMatrix();

    //Render the GUI in device space
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 0, 800, 640, 0, -1, 1 );

	//Render the GUI in device space
	glMatrixMode(GL_MODELVIEW);
	glPolygonMode( GL_FRONT, GL_FILL );

    if (font != NULL) {
    	renderText(font, 0, 0, "Score: 0");
    }

    SDL_GL_SwapWindow(window);

}

void Display::renderText(const TTF_Font *font, float32 x, float32 y, const std::string& text) {
	SDL_Color colour = {255, 255, 255};
	SDL_Surface *message = TTF_RenderText_Blended(const_cast<TTF_Font*>(font), text.c_str(), colour);
	unsigned int texture = 0;

	//create a texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, message->w, message->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, message->pixels);

		/*Draw this texture on a quad with the given xyz coordinates.*/
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
			glTexCoord2d(0, 0); glVertex3d(x, y, 0);
			glTexCoord2d(1, 0); glVertex3d(x+message->w, y, 0);
			glTexCoord2d(1, 1); glVertex3d(x+message->w, y+message->h, 0);
			glTexCoord2d(0, 1); glVertex3d(x, y+message->h, 0);
		glEnd();

		/*Clean up.*/
		glDeleteTextures(1, &texture);
		SDL_FreeSurface(message);
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

