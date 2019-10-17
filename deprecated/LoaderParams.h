#ifndef __LoaderParams_H__
#define __LoaderParams_H__

#include "Vector2D.h"

class LoaderParams
{
  private:
	// 坐标
	Vector2D m_position;
	// 速度
	Vector2D m_velocity;
	// 加速度
	Vector2D m_acceleration;
  public:
	LoaderParams(int x, int y, int speed_x, int speed_y, int accele_x, int accele_y)
	:m_position(x, y), m_velocity(speed_x, speed_y),
		m_acceleration(accele_x, accele_y)
	{
	}
	Vector2D getPosition()
	{
		return m_position;
	}
	Vector2D getVelocity()
	{
		return m_velocity;
	}
	Vector2D getAcceleration()
	{
		return m_acceleration;
	}
};
#endif