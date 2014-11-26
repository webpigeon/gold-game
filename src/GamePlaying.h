/*
 * GamePlaying.h
 *
 *  Created on: 25 Nov 2014
 *      Author: webpigeon
 */

#ifndef GAMEPLAYING_H_
#define GAMEPLAYING_H_

#include "GameState.h"
#include "model/World.h"
#include "model/Model.h"

class GamePlaying: public GameState {
public:
	GamePlaying();
	void enterState(DisplayUtils* utils);
	void update(int delta);
	void render(DisplayUtils* context);
	void renderGUI(DisplayUtils* context);
	void keyPressed(int keyCode);
	virtual ~GamePlaying();

private:
	World* world;
	Entity* player;
	Model* model;
	DisplayUtils* utils;
};

#endif /* GAMEPLAYING_H_ */
