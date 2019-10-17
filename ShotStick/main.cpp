#include <iostream>
#include <string>
#include "SDL.h"
#include "Game.h"

int main(int argc,char**argv)
{
	if (TheGame::getInstance()->init("Shot Stick"
		,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
		,960,640,SDL_WINDOW_SHOWN))
	{
		while (TheGame::getInstance()->running())
		{
			TheGame::getInstance()->update();
			TheGame::getInstance()->render();
			TheGame::getInstance()->handleEvents();
		}
	}
	else
	{
	    std::cout<<"error:"<<SDL_GetError()<<std::endl;
		return -1;
	}
	TheGame::getInstance()->clean();

	return 0;
}