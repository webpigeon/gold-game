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
#include "world.h"

class Model : public b2ContactListener {
public:
	Model(World* world, Entity* player);
	virtual ~Model();

	void fire();
	void accelerate(int delta);
	void turn(int direction);

	Entity* getPlayer();
	bool isPlayerAlive();

	Audio audio;
	//callbacks for contact detection
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
private:
	World* world;
	int score;
	uint32 weaponLastFired;
	Entity* player;
};

#endif /* MODEL_H_ */
