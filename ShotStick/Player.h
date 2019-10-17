#ifndef __Player_H__
#define __Player_H__
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"
using namespace std;

class Player: public GameObject
{
  public:
	  Player();
	 ~Player();
	 bool init(const string& spriteID);

	 void setVelocity(const Vector2D& velocity);

	 virtual void update();
	 virtual void draw(SDL_Renderer* ren);
	 virtual void clean();
  private:
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;
	string m_spriteID;
};
#endif