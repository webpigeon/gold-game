/*
 * Model.cpp
 *
 *  Created on: 23 Nov 2014
 *      Author: webpigeon
 */

#include "Model.h"
#include <iostream>

using namespace std;

Model::Model() {
	// TODO Auto-generated constructor stub

}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

void Model::BeginContact(b2Contact* contact){
	b2Body* b1 = contact->GetFixtureA()->GetBody();
	b2Body* b2 = contact->GetFixtureB()->GetBody();

	void* userData1 = b1->GetUserData();
	if (userData1) {

	}

	void* userData2 = b2->GetUserData();
	if (userData2) {

	}

	std::cout << "collision detected " << contact->IsTouching() << std::endl;



}

void Model::EndContact(b2Contact* contact){


}
