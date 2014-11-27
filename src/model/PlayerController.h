/*
 * PlayerController.h
 *
 *  Created on: 27 Nov 2014
 *      Author: webpigeon
 */

#ifndef PLAYERCONTROLLER_H_
#define PLAYERCONTROLLER_H_

#include "Component.h"
#include "Entity.h"

#define DIR_FORWARD 1
#define DIR_REVERSE -1
#define DIR_LEFT -1
#define DIR_RIGHT 1
#define DIR_NONE 0

class PlayerController : public Component<Entity> {
public:
	PlayerController();
	virtual ~PlayerController();
	void onBind(Entity* entity);
	void update(int delta);

	void setFiring(bool toggle);
	void setAccelerating(int dir);
	void setTurning(int dir);
private:
	Entity* entity;
	bool firing;
	int acceleration;
	int turning;
};

#endif /* PLAYERCONTROLLER_H_ */
