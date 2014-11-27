/*
 * GameMessage.cpp
 *
 *  Created on: 26 Nov 2014
 *      Author: webpigeon
 */

#include "GameMessage.h"

GameMessage::GameMessage(std::string message) {
	this->message = message;
}

void GameMessage::enterState(DisplayUtils* utils){
	this->utils = utils;
}

void GameMessage::update(int delta){}

void GameMessage::render(DisplayUtils* context){
}

void GameMessage::renderGUI(DisplayUtils* context) {
	context->renderText(-1, 200, message);
	context->renderText(-1, 370, "Press space to continue");
}

void GameMessage::keyPressed(int keyCode){
	if (keyCode == SDLK_SPACE){
		utils->changeState("playing");
	}
}

void GameMessage::keyReleased(int keyCode){}

GameMessage::~GameMessage() {
	// TODO Auto-generated destructor stub
}

