/*
 * GamePlaying.cpp
 *
 *  Created on: 25 Nov 2014
 *      Author: webpigeon
 */

#include "GamePlaying.h"
#include "model/MapReader.h"

#include <cstdlib>

GamePlaying::GamePlaying() {
	this->level = 0;
	this->levelCount = 2;
	this->levels = new std::string[levelCount];
	this->levels[0] = "Assets/Maps/tutorial-1.bmp";
	this->levels[1] = "Assets/Maps/map2.bmp";
}

void GamePlaying::enterState(DisplayUtils* utils){
	this->utils = utils;
	world = new World;


	// we have no more levels
	if (level >= levelCount) {
		exit(0);
	}

	MapReader reader;
	std::string mapName = levels[level];

	b2Vec2 playerLocation;
	reader.loadMap(mapName.c_str(), world, playerLocation);

	player = world->addShip(playerLocation.x, playerLocation.y);

	model = new Model(world, player);
	world->addColliderCallback(model);
}

void GamePlaying::keyPressed(int keyCode) {
	switch(keyCode) {

		        		case SDLK_UP:
		        			model->accelerateStarted(-1);
		        			break;

		        		case SDLK_DOWN:
		        			model->accelerateStarted(1);
		        			break;

		        		case SDLK_LEFT:
		        			model->turnStarted(-1);
		        			break;

		        		case SDLK_RIGHT:
		        			model->turnStarted(1);
		        			break;

		        		case SDLK_SPACE:
		        			model->fireStarted();
		        			break;
		        	}


}

void GamePlaying::keyReleased(int keyCode) {
	switch(keyCode) {
						case SDLK_DOWN:
		        		case SDLK_UP:
		        			model->accelerateStarted(0);
		        			break;

		        		case SDLK_RIGHT:
		        		case SDLK_LEFT:
		        			model->turnStarted(0);
		        			break;

		        		case SDLK_SPACE:
		        			//model->fireStarted();
		        			break;
		        	}


}

void GamePlaying::update(int delta){
    world->update(delta);

    if (!model->isPlayerAlive()){
    	utils->changeState("gameover-lose");
    }

    if (model->hasPlayerWon()) {
    	level++;
    	if (level < levelCount) {
    		utils->changeState("complete");
    	} else {
    		std::cout << "all maps complete" << std::endl;
    		utils->changeState("gameover-win");
    	}
    }
}

void GamePlaying::render(DisplayUtils* context){

    if (player != NULL && player->getBody() != NULL) {
    	b2Vec2 playerPos = player->getBody()->GetWorldCenter();
    	glTranslatef(-playerPos.x + 40, -playerPos.y + 30, 0);
    }

    world->draw();
}

void GamePlaying::renderGUI(DisplayUtils* context){
	char scoreStr[40];
	sprintf ( scoreStr, "score: %d", model->getScore() );

	context->renderText(0, 0, string(scoreStr));
}

GamePlaying::~GamePlaying() {
	delete model;
	delete world;
}

