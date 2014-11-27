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
	// TODO Auto-generated constructor stub
}

void GamePlaying::enterState(DisplayUtils* utils){
	this->utils = utils;
	world = new World;


	MapReader reader;
	b2Vec2 playerLocation;
	reader.loadMap("Assets/Maps/map1.bmp", world, playerLocation);

	player = world->addShip(playerLocation.x, playerLocation.y);

	model = new Model(world, player);
	world->addColliderCallback(model);
}

void GamePlaying::keyPressed(int keyCode) {
	switch(keyCode) {

		        		case SDLK_UP:
		        			model->accelerate(-1);
		        			break;

		        		case SDLK_DOWN:
		        			model->accelerate(1);
		        			break;

		        		case SDLK_LEFT:
		        			model->turn(-1);
		        			break;

		        		case SDLK_RIGHT:
		        			model->turn(1);
		        			break;

		        		case SDLK_SPACE:
		        			model->fire();
		        			break;
		        	}


}

void GamePlaying::update(int delta){
    world->update(delta);

    /*if (!model->isPlayerAlive()){
    	utils->changeState("gameover");
    }*/
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

