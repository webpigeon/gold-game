/*
 * GameOver.h
 *
 *  Created on: 26 Nov 2014
 *      Author: webpigeon
 */

#include "GameState.h"

#ifndef GAMEOVER_H_
#define GAMEOVER_H_

class GameMessage : public GameState {
public:
	GameMessage(std::string message);
	void enterState(DisplayUtils* utils);
	void update(int delta);
	void render(DisplayUtils* context);
	void renderGUI(DisplayUtils* context);
	void keyPressed(int keyCode);
	void keyReleased(int keyCode);
	virtual ~GameMessage();

private:
	DisplayUtils* utils;
	std::string message;
};

#endif /* GAMEOVER_H_ */
