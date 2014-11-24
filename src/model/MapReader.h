/*
 * MapReader.h
 *
 *  Created on: 24 Nov 2014
 *      Author: piers
 */

#ifndef MAPREADER_H_
#define MAPREADER_H_

#include <vector>
#include "Entity.h"

using namespace std;

class MapReader {
public:
	MapReader();
	virtual ~MapReader();

	vector<Entity>* loadMap(char* name);
};

#endif /* MAPREADER_H_ */
