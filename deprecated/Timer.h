#ifndef __Timer_H__
#define __Timer_H__

#include "SDL.h"
// Timer类
class Timer
{
  private:
	// 计时器启动的时间
	int startTicks;
	// 计时器暂停是保存的时间
	int pausedTicks;
	// 计时器状态
	bool paused;
	bool started;
  public:
	Timer()
	{
		startTicks = 0;
		pausedTicks = 0;
		paused = false;
		started = false;
	}
	void start();
	void stop();
	void pause();
	void unpause();
	// 获取计时器时间
	int get_ticks();
	// 检查计时器状态
	bool is_started() const;
	bool is_paused() const;
};

#endif