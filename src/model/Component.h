/*
 * Component.h
 *
 *  Created on: 27 Nov 2014
 *      Author: webpigeon
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

template<typename T>
class Component {
public:
	virtual ~Component() {};
	virtual void onBind(T* parent) = 0;
	virtual void update(int delta) = 0;
};

#endif /* COMPONENT_H_ */
