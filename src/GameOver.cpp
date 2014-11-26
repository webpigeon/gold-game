/*
 * GameOver.cpp
 *
 *  Created on: 26 Nov 2014
 *      Author: webpigeon
 */

#include "GameOver.h"

GameOver::GameOver() {
	// TODO Auto-generated constructor stub

}

void GameOver::enterState(DisplayUtils* utils){
	this->utils = utils;
}

void GameOver::update(int delta){}

void GameOver::render(DisplayUtils* context){
}

void GameOver::renderGUI(DisplayUtils* context) {
	context->renderText(360, 200, "Game Over");
	context->renderText(320, 370, "Press space to restart");
}

void GameOver::keyPressed(int keyCode){
	if (keyCode == SDLK_SPACE){
		utils->changeState("playing");
	}
}

GameOver::~GameOver() {
	// TODO Auto-generated destructor stub
}

