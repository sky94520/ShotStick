#ifndef __Game_H__
#define __Game_H__

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

#include "SDL.h"

class ShotStick;
class Player;
class ShotStick;

class Game
{
private:
	static Game*s_pInstance;
	Game();
public:
     static Game* getInstance();
     //初始化
     bool init(const char *title, int xpos, int ypos, int width, int height, int flags);
     void render();
	 void update();
	 void handleEvents();
	 void clean();

	 SDL_Renderer* getRenderer() const { return m_pRenderer; }
	 bool running() const { return m_bRunning; }

	 int getGameWidth() const { return m_gameWidth; }
	 int getGameHeight() const { return m_gameHeight; }
private:
	//SDL窗口 渲染器
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	//是否运行
	bool m_bRunning;
	//屏幕大小
	int m_gameWidth;
	int m_gameHeight;

	Player* m_pPlayer;
	ShotStick* m_pShotStick;
};
typedef Game TheGame;
#endif