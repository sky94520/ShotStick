#include "Fps.h"

Fps::Fps(int frame) : m_nFrame(frame)
{
    m_nCurFrame = 0;
    m_nLastFrame = 0;
}
int Fps::getFPS()
{
    //启东计时器
    if (!m_limitTime.is_started())
       m_limitTime.start();
    if (m_limitTime.get_ticks() >= 1000)
    {
        m_nLastFrame = m_nCurFrame;
        m_nCurFrame = 0;
        m_limitTime.start();
    }
    m_nCurFrame++;
    
     //若未达到,则delay
     if (m_limitTime.get_ticks() < 1000/m_nFrame)
           SDL_Delay(1000/m_nFrame - m_limitTime.get_ticks());

    return m_nLastFrame;
}
