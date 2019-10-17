#ifndef __ShotStick_H__
#define __ShotStick_H__

#include <cmath>
#include <string>

#include "SDL.h"
#include "GameObject.h"
#include "Vector2D.h"

#define PI 3.1415926

typedef struct Cicrcle
{
	int x;
	int y;
	double radius;
}Circle;

typedef struct Point
{
	double x;
	double y;
}Point;
/*虚拟摇杆*/
class ShotStick : public GameObject
{
public:
	ShotStick(const std::string& rockerID, const std::string& backgroundID);
	virtual ~ShotStick();
	virtual bool load(LoaderParams*pParams);
	virtual void draw(SDL_Renderer*ren);
	virtual void update();
	virtual void clean();
	
	Vector2D getVelocity();
	void handleEvents(SDL_Event* event);
	//void handleEventsInWin(SDL_Event* event);
 private:
	//外圆
    Circle m_outCircle;
    //内方形
    Circle m_inCircle;
    //有效相对于圆心触屏坐标,
    Point m_relativePoint;
    //绑定一个有效的手指
    SDL_FingerID m_fingerId;
	//摇杆图片ID和背景ID
	std::string m_rockerID;
	std::string m_backgroundID;
};
#endif