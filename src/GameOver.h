/*
 * GameOver.h
 *
 *  Created on: 26 Nov 2014
 *      Author: webpigeon
 */

#include "GameState.h"

#ifndef GAMEOVER_H_
#define GAMEOVER_H_

class GameOver : public GameState {
public:
	GameOver();
	void enterState();
	void update(int delta);
	void render(SDL_GLContext* context);
	void keyPressed(int keyCode);
	virtual ~GameOver();
};

#endif /* GAMEOVER_H_ */
