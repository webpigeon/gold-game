/*
 * GamePlaying.h
 *
 *  Created on: 25 Nov 2014
 *      Author: webpigeon
 */

#ifndef GAMEPLAYING_H_
#define GAMEPLAYING_H_

#include "GameState.h"
#include "model/world.h"
#include "model/Model.h"

class GamePlaying: public GameState {
public:
	GamePlaying();
	void enterState();
	void update(int delta);
	void render(SDL_GLContext* context);
	void renderText(SDL_GLContext* context);
	void keyPressed(int keyCode);
	virtual ~GamePlaying();

private:
	World* world;
	Entity* player;
	Model* model;
};

#endif /* GAMEPLAYING_H_ */
