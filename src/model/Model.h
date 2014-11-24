/*
 * Model.h
 *
 *  Created on: 23 Nov 2014
 *      Author: webpigeon
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <Box2D/Box2D.h>

class Model : public b2ContactListener {
public:
	Model();
	virtual ~Model();

	//callbacks for contact detection
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

#endif /* MODEL_H_ */
