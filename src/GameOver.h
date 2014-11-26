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
	void enterState(DisplayUtils* utils);
	void update(int delta);
	void render(DisplayUtils* context);
	void renderGUI(DisplayUtils* context);
	void keyPressed(int keyCode);
	virtual ~GameOver();

private:
	DisplayUtils* utils;
};

#endif /* GAMEOVER_H_ */
