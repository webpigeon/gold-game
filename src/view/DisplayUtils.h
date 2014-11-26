/*
 * DisplayUtils.h
 *
 *  Created on: 26 Nov 2014
 *      Author: webpigeon
 */

#ifndef DISPLAYUTILS_H_
#define DISPLAYUTILS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <Box2D/Box2D.h>

#include <string>

class DisplayUtils {
public:
	virtual ~DisplayUtils() {};
	virtual void renderText(float32 x, float32 y, const std::string& Text) = 0;
};

#endif /* DISPLAYUTILS_H_ */
