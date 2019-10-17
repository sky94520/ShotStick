#include "Timer.h"

void Timer::start()
{
	// 启动计时器
	started = true;
	paused = false;
	// 获取当前时钟时间
	startTicks = SDL_GetTicks();
}

void Timer::stop()
{
	// 停止计时器
	started = false;
	paused = false;

	startTicks = 0;
}

int Timer::get_ticks()
{
	if (started == true)
	{
		if (paused == true)
			return pausedTicks;
		else
			return SDL_GetTicks() - startTicks;
	}
}

void Timer::pause()
{
	if ((started == true) && (paused == false))
	{
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause()
{
	if (paused == true)
	{
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

bool Timer::is_started() const
{
	return started;
}

bool Timer::is_paused() const
{
	return paused;
}