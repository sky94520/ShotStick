#include "ShotStick.h"
#include "Game.h"
#include "TextureManager.h"

ShotStick::ShotStick()
	:m_fingerId(-1)//当前无手指绑定
{
	m_relativePoint.x = 0;
	m_relativePoint.y = 0;
}

ShotStick::~ShotStick()
{
}

bool ShotStick::init(const std::string& rockerID, const std::string& backgroundID)
{
	m_rockerID = rockerID;
	m_backgroundID = backgroundID;
	//获取摇杆rect
	SDL_Rect rect1 = TheTextureManager::Instance()->getTextureRectFromId(rockerID);
	SDL_Rect rect2 = TheTextureManager::Instance()->getTextureRectFromId(backgroundID);
	//圆半径
	m_outCircle.radius = rect1.w/2;
	m_inCircle.radius = rect2.w/2;

	return true;
}

void ShotStick::draw(SDL_Renderer * ren)
{
	// 画出虚拟摇杆画出外圆
	int screenW = TheGame::getInstance()->getGameWidth();
	int screenH = TheGame::getInstance()->getGameHeight();
	// 圆心
	m_inCircle.x = m_outCircle.x = m_outCircle.radius;
	m_inCircle.y = m_outCircle.y = screenH - m_outCircle.radius;

	TheTextureManager::Instance()->draw(m_rockerID
		,m_outCircle.x - m_outCircle
		.radius,m_outCircle.y - m_outCircle.radius);
	// 画出内圆
	TheTextureManager::Instance()->draw(m_backgroundID
		,m_inCircle.x + m_relativePoint.x - m_inCircle.radius
		,m_inCircle.y + m_relativePoint.y - m_inCircle.radius);
}

void ShotStick::update()
{
}

Vector2D ShotStick::getVelocity()
{
	double x = m_relativePoint.x;
	double y = m_relativePoint.y;
	double r = std::sqrt(x * x + y * y);
	if (r == 0)
		return Vector2D(0, 0);
	/* sin = y/r; cos = x/r; */
	r = m_outCircle.radius;
	return Vector2D(x / r, y / r);
}

void ShotStick::handleEvents(SDL_Event* event)
{
	switch (event->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{
			if (event->button.button != SDL_BUTTON_LEFT)
				break;
			Sint32 x = event->motion.x, y = event->motion.y;
			auto distance = std::sqrt(std::pow(x - m_outCircle.x, 2) + std::pow(y - m_outCircle.y, 2));
			//超出距离
			if (distance > m_outCircle.radius) {
				m_fingerId = -1;
				break;
			}
			else
				m_fingerId = 0;
		}
		case SDL_MOUSEMOTION:
		{
			if (m_fingerId == -1)
				break;
			Sint32 x = event->motion.x, y = event->motion.y;
			//保证不会超过摇杆背景圆
			double x_average = x - m_outCircle.x;
			double y_average = y - m_outCircle.y;
			double d = std::sqrt(std::pow(x_average, 2) + std::pow(y_average, 2));
			
			double m = d > m_outCircle.radius ? m_outCircle.radius : d;
			m_relativePoint.x = m * (x_average / d);
			m_relativePoint.y = m * (y_average / d);
		}break;
		case SDL_MOUSEBUTTONUP:
		{
			if (event->button.button != SDL_BUTTON_LEFT)
				break;
			m_fingerId = -1;
			m_relativePoint.x = 0.0;
			m_relativePoint.y = 0.0;
		}break;
		case SDL_FINGERDOWN:
		{
			SDL_Finger finger;
			finger.x = event->tfinger.x * TheGame::getInstance()->getGameWidth();
			finger.y = event->tfinger.y * TheGame::getInstance()->getGameHeight();
			// 绑定有效id
			if (m_fingerId == -1
				&& std::sqrt(std::pow(finger.x - m_outCircle.x, 2) +
							 std::pow(finger.y - m_outCircle.y,
									  2)) <= m_outCircle.radius)
				m_fingerId = event->tfinger.fingerId;
		}
		case SDL_FINGERMOTION:
		{
			SDL_FingerID id = event->tfinger.fingerId;
			// 如果不相等，退出
			if (m_fingerId != id)
				break;
			SDL_Finger finger;
			finger.id = id;
			finger.x = event->tfinger.x * TheGame::getInstance()->getGameWidth();
			finger.y = event->tfinger.y * TheGame::getInstance()->getGameHeight();
			
			double x_average = finger.x - m_outCircle.x;
			double y_average = finger.y - m_outCircle.y;
			double d = std::sqrt(std::pow(x_average, 2) + std::pow(y_average, 2));
			
			double m = d > m_outCircle.radius ? m_outCircle.radius : d;
			m_relativePoint.x = m * (x_average / d);
			m_relativePoint.y = m * (y_average / d);
		}break;
		case SDL_FINGERUP:
		{
			SDL_FingerID id = event->tfinger.fingerId;
			// 如果为有效id
			if (id == m_fingerId)
			{
				m_relativePoint.x = 0;
				m_relativePoint.y = 0;
				m_fingerId = -1;
			}
		}break;
	}// end switch
}

void ShotStick::clean()
{
}