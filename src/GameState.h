/*
 * GameState.h
 *
 *  Created on: 25 Nov 2014
 *      Author: webpigeon
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <SDL2/SDL.h>
#include <GL/gl.h>

class GameState {
public:
	GameState();
	virtual void enterState() = 0;
	virtual void update(int delta) = 0;
	virtual void render(SDL_GLContext* context) = 0;
	virtual void keyPressed(int keyCode) = 0;
	virtual ~GameState();
};

#endif /* GAMESTATE_H_ */
