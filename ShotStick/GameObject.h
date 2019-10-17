#ifndef __GameObject_H__
#define __GameObject_H__

#include "LoaderParams.h"
class GameObject
{
 public:
	virtual void update() = 0;
	virtual void draw(SDL_Renderer*ren) = 0;
	virtual void clean() = 0;
};
#endif