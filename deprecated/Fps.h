#ifndef __Fps_H__
#define __Fps_H__

#include "SDL.h"
#include "Timer.h"

class Fps
{
 private:
    //限制的帧数 默认为60
    const int m_nFrame;
    //计时器 限制多少毫秒
    Timer m_limitTime;
    //上一秒运行的帧数
    int m_nLastFrame;
    //当前帧数
    int m_nCurFrame;
 public:
    Fps(int frame = 60);
    int getFPS();
};

#endif