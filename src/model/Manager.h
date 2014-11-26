/*
 * Manager.h
 *
 * Manager interface, used to prevent circular dependencies in world
 *
 *  Created on: 25 Nov 2014
 *      Author: webpigeon
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include <vector>

template<typename T>
class Manager {
public:
	virtual ~Manager() {};
	virtual void add(T* element) = 0;
	virtual void remove(T* element) = 0;
	virtual std::vector<T*>* inRange(b2Vec2 location, float32 range, T* nearest) = 0;
	virtual b2Body* buildBody(b2BodyDef* bodyDef) = 0;
};

#endif /* MANAGER_H_ */
