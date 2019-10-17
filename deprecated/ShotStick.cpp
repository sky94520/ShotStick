#include "ShotStick.h"
#include "Game.h"
#include "TextureManager.h"

ShotStick::ShotStick(const std::string& rockerID, const std::string& backgroundID)
	:m_rockerID(rockerID)
	,m_backgroundID(backgroundID)
{
	m_relativePoint.x = 0;
	m_relativePoint.y = 0;
	// 当前无手指绑定
	m_fingerId = -1;
	
	//获取摇杆rect
	SDL_Rect rect1 = TheTextureManager::Instance()->getTextureRectFromId(rockerID);
	SDL_Rect rect2 = TheTextureManager::Instance()->getTextureRectFromId(backgroundID);
	//圆半径
	m_outCircle.radius = rect1.w/2;
	m_inCircle.radius = rect2.w/2;
}

ShotStick::~ShotStick()
{
}

bool ShotStick::load(LoaderParams * pParams)
{
	return true;
}

void ShotStick::draw(SDL_Renderer * ren)
{
	/* 画出虚拟摇杆 */
	// 画出外圆
	int screenW = TheGame::Instance()->getGameWidth();
	int screenH = TheGame::Instance()->getGameHeight();
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
	return Vector2D(x / r, y / r);
}

void ShotStick::handleEvents(SDL_Event* event)
{
	switch (event->type)
	{
		case SDL_FINGERDOWN:
		{
			SDL_Finger finger;
			finger.x = event->tfinger.x * TheGame::Instance()->getGameWidth();
			finger.y = event->tfinger.y * TheGame::Instance()->getGameHeight();
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
			finger.x = event->tfinger.x * TheGame::Instance()->getGameWidth();
			finger.y = event->tfinger.y * TheGame::Instance()->getGameHeight();
			
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