/*
 * Model.h
 *
 *  Created on: 23 Nov 2014
 *      Author: webpigeon
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <Box2D/Box2D.h>

#include "Audio.h"
#include "World.h"
#include "PlayerController.h"

class Model : public b2ContactListener {
public:
	Model(World* world, Entity* player);
	virtual ~Model();

	void fireStarted();
	void fireStopped();

	void accelerateStarted(int delta);
	void accelerateStopped();

	void turnStarted(int direction);
	void turnStopped();

	Entity* getPlayer();
	bool hasPlayerWon();
	bool isPlayerAlive();
	int getScore();

	Audio audio;
	//callbacks for contact detection
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
private:
	PlayerController* controller;
	World* world;
	int score;
	int goalsLeft;
	uint32 weaponLastFired;
	Entity* player;
};

#endif /* MODEL_H_ */
